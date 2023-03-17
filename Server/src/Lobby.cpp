/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLogic.cpp
*/

#include "../include/Lobby.hpp"
#include "../include/utils/shutdown.hpp"
#include "../../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../../Lib/GameEngine/include/Components/Cooldown.hpp"

Server::Lobby::Lobby(const unsigned short int &port, std::shared_ptr<Network::SafeQueue<Network::Message<Thread::codes>>> &threadMsgOutput)
: _port(port), _inGame(false), _threadMsgOutput(threadMsgOutput), _alive(true),
 _threadMsgInput(std::make_shared<Network::SafeQueue<Network::Message<Thread::codes>>>())
{
    _uuid = createUuid();
    _name = "Lobby " + std::to_string(_uuid);
    _server = std::make_shared<Network::ServerData<Network::Codes>>("127.0.0.1", port);
    _msgList = _server->getClientMsg();
    _entityManager = std::make_shared<GameEngine::EntityManager>();
    _enemies = std::make_unique<Server::Enemy>(_entityManager, _server);
    _rockets = std::make_unique<Server::Rocket>(_entityManager, _server);
    _players = std::make_unique<Server::Player>(_entityManager, _server);
    _wall = std::make_unique<Server::Wall>(_entityManager, _server);
    _powerUp = std::make_unique<Server::PowerUp>(_entityManager, _server);
	_server->start();
	std::cout << "[LOBBY CREATED]: " << _name << std::endl;
	_lobbyThread = std::thread(&Lobby::run, this);
}



Server::Lobby::~Lobby()
{
	if (_lobbyThread.joinable())
		_lobbyThread.join();
	_server->stop();
	std::cout << "[LOBBY CLOSED]: " << _uuid << std::endl;
}

std::string Server::Lobby::getName() const
{
    return (_name);
}

uint32_t Server::Lobby::getUuid() const
{
    return (_uuid);
}

unsigned short int Server::Lobby::getPort() const
{
	return _port;
}

GameEngine::Actions getActionsFromClient(uint8_t actionInUint8)
{
    switch (static_cast<int>(actionInUint8)) {
        case GameEngine::MOVE_LEFT:
            return (GameEngine::MOVE_LEFT);
        case GameEngine::MOVE_RIGHT:
            return (GameEngine::MOVE_RIGHT);
        case GameEngine::MOVE_DOWN:
            return (GameEngine::MOVE_DOWN);
        case GameEngine::MOVE_UP:
            return (GameEngine::MOVE_UP);
        case GameEngine::SHOOT:
            return (GameEngine::SHOOT);
        default:
            return (GameEngine::NOTHING);
    }
}

void Server::Lobby::sendUpdate()
{
    for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
        Network::Message<Network::Codes> messageUpdate;
        messageUpdate.header.header_id = Network::UPDATE_ENTITIES;
        if (_entityManager->getEntityList()[i]->hasComp<GameEngine::Health>())
            messageUpdate << (_entityManager->getEntityList()[i]->getComp<GameEngine::Health>()->_health);
        if (_entityManager->getEntityList()[i]->hasComp<GameEngine::Position>()) {
            messageUpdate << static_cast<uint16_t>(_entityManager->getEntityList()[i]->getComp<GameEngine::Position>()->getPosition().y);
            messageUpdate << static_cast<uint16_t>(_entityManager->getEntityList()[i]->getComp<GameEngine::Position>()->getPosition().x);
        }
        messageUpdate << static_cast<uint8_t>(_entityManager->getEntityList()[i]->_type);
        messageUpdate << static_cast<uint32_t>(_entityManager->getEntityList()[i]->_id);
        _server->notifiyClients(messageUpdate);
    }
}

void Server::Lobby::updatePlayerLobby()
{
	Network::Message<Network::Codes> msg;

	msg.header.header_id = Network::PLAYER_LIST_LOBBY;
	for (int i = 0; i < _players->_playerList.size(); i++)
		msg << _players->_playerList[i]->_id;
	_server->notifiyClients(msg);
}

void Server::Lobby::getMessages()
{
    while (!_msgList->isEmpty()) {
        auto owner = _msgList->front();
        // if the message is an actions from a player
		//std::cout << owner.msg.header.header_id << std::endl;
		if (owner.msg.header.header_id == Network::HELLO_LOBBY) {
			uint32_t id;
			owner.msg >> id;
			owner.client->setId(id);
			addPlayer(id);
			Network::Message<Network::Codes> msg;
			msg.header.header_id = Network::PLAYER_LIST_LOBBY;
			for (int i = 0; i < _players->_playerList.size(); i++)
				msg << _players->_playerList[i]->_id;
			_server->send(owner.client, msg);
			updatePlayerLobby();
			_server->append_client(std::move(owner.client));
			std::cout << "[INFO]: " << id << " joined lobby " << _uuid << std::endl;
		}
        if (owner.msg.header.header_id == Network::MOVE) {
            uint32_t ID;
            int8_t Action;
            owner.msg >> Action;
            owner.msg >> ID;
            for (int i = 0; i <_players->_playerList.size(); i++) {
//                 check if the id_entity of the message is the same as the id of the player
                if (_players->_playerList[i]->_id == ID) {
                    // Push the message in the action queue of the player
                    _players->_actionQueue[i].push_back(getActionsFromClient(Action));
                }
            }
        }
        if (owner.msg.header.header_id == Network::SHOOT) {
            uint32_t ID;
            owner.msg >> ID;
            for (int i = 0; i <_players->_playerList.size(); i++) {
//                 check if the id_entity of the message is the same as the id of the player
                if (_players->_playerList[i]->_id == ID) {
                    // Push the message in the action queue of the player
                    _players->_actionQueue[i].push_back(GameEngine::SHOOT);
                }
            }
        }
		if (owner.msg.header.header_id == Network::START_GAME) {
			_inGame = true;
			std::cout << "[INFO]: Game started in lobby " << _uuid << std::endl;
		}
		if (owner.msg.header.header_id == Network::LEAVE) {
			uint32_t id = 0;
			owner.msg >> id;
			_server->remove_client(id);
			_players->popPlayer(id);
			if (getNumberPlayers() == 0) {
				_alive = false;
				Network::Message<Thread::codes> quitMessage;

				quitMessage.header.header_id = Thread::KILL;
				quitMessage << _uuid;
				_threadMsgOutput->push(quitMessage);
			}
			updatePlayerLobby();
		}
        _msgList->pop();
    }
}

uint32_t Server::Lobby::getIdLastPlayer()
{
    return (_players->_playerList.back()->_id);
}

int Server::Lobby::getNumberPlayers() const
{
    return (_players->_playerList.size());
}

void Server::Lobby::sendMessage(const Network::Message<Thread::codes> &msg)
{
	_threadMsgInput->push(msg);
}

void Server::Lobby::addPlayer(const uint32_t &id)
{
    _players->addPlayer(_entityManager->CreatePlayer());
	_players->_playerList.back()->_id = id;
    _players->_playerList.back()->getComp<GameEngine::Hitbox>()->_hitbox = {140, 90, 280, 80};
    uint16_t randx = rand() % 500;
    uint16_t randy = rand() % 1000;
    _players->_playerList.back()->getComp<GameEngine::Position>()->setPosition(randx, randy);
    _players->_playerList.back()->getComp<GameEngine::Cooldown>()->setMaxCooldownInMS(250);
}

void Server::Lobby::getAllScores(void) 
{   
    uint32_t backupScore = _score;
    _score += _enemies->_score;
    _enemies->_score = 0;
    _score += _powerUp->_score;
    _powerUp->_score = 0;
    _score += _wall->_score;
    _wall->_score = 0;
    if (backupScore != _score) {
        sendScore();
    }
}

void Server::Lobby::sendScore(void)
{
    Network::Message<Network::Codes> msg;
    msg.header.header_id = Network::SCORE;
    msg << _score;
    _server->notifiyClients(msg);
}

void Server::Lobby::run()
{
    Clock timer;

	while (!stop && _alive) {
		timer.startClock();
		getMessages();
        
		if (_inGame) {
            srand (time(NULL));
			_players->run();
			_enemies->run();
			_rockets->run();
            _powerUp->run();
            _wall->run();
            getAllScores();
			sendUpdate();
		}
		timer.endClock();
		timer.wait();
	}
}
