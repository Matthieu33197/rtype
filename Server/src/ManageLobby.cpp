/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ManageClients source file
*/

#include "../include/ManageLobby.hpp"
#include "../include/utils/shutdown.hpp"

bool stop = false;

void handle_signal(int num)
{
	stop = true;
}

Server::ManageLobby::ManageLobby(const unsigned short int &port)
: _port(port), _lobbyPort(port + 5),
  _server(std::make_shared<Network::ServerCommand<Network::Codes>>("127.0.0.1", port)),
  _processMsg(std::make_shared<Network::SafeQueue<Network::Message<Thread::codes>>>()),
  _msgList(_server->getClientMsg())
{
	std::signal(SIGINT, handle_signal);
}

void Server::ManageLobby::readProcessMessages()
{
	while (!_processMsg->isEmpty()) {
		auto pMsg = _processMsg->front();
		if (pMsg.header.header_id == Thread::KILL) {
			uint32_t id = 0;
			pMsg >> id;
			if (_listLobby.find(id) != _listLobby.end()) {
				_listLobby.erase(id);
				std::cout << "deleted" << std::endl;
				updateLobbyList();
				updateLobbyList();
			}
		}
		_processMsg->pop();
	}
}

void Server::ManageLobby::updateLobbyList()
{
	Network::Message<Network::Codes> message;
	message.header.header_id = Network::LOBBY_LIST;
	for (const auto &[uuid, lobby] : _listLobby) {
		message << lobby->getNumberPlayers() << lobby->getUuid();
	}
	std::function<void(const uint32_t &)> empty = [](const uint32_t &t){};
	_server->notifiyClients(message, empty);
}

void Server::ManageLobby::getMessages()
{
    _msgList = _server->getClientMsg();
    while (!_msgList->isEmpty()) {
        auto owner = _msgList->front();
        // if the message is an actions from a player
        if (owner.msg.header.header_id == Network::HELLO_TCP) {
			Network::Message<Network::Codes> message;
			message.header.header_id = Network::ID_PLAYER;
			owner.client->setId(createUuid());
			message << owner.client->getId();
			_server->send(owner.client, message);
            std::cout << "-- TCP Connected --" << std::endl;
        }
        if (owner.msg.header.header_id == Network::CREATE_LOBBY) {
            std::cout << "CREATE LOBBY" << std::endl;
            Network::Message<Network::Codes> message;
			message.header.header_id = Network::LOBBY_PORT;
			std::unique_ptr<Server::Lobby> newLobby = std::make_unique<Server::Lobby>(_lobbyPort, _processMsg);
            _listLobby[newLobby->getUuid()] = std::move(newLobby);
            message << static_cast<uint16_t>(_lobbyPort);
            _server->send(owner.client, message);
			updateLobbyList();
			_lobbyPort += 5;
        }
        if (owner.msg.header.header_id == Network::JOIN_LOBBY) {
            uint32_t uuid;
            owner.msg >> uuid;
			Network::Message<Network::Codes> message;
			if (_listLobby.find(uuid) == _listLobby.end()) {
				message.header.header_id = Network::UNKNOWN;
			} else {
				message.header.header_id = Network::LOBBY_PORT;
                //std::cout << _listLobby[uuid]->getPort() << std::endl;
				message << static_cast<uint16_t>(_listLobby[uuid]->getPort());
			}
			_server->send(owner.client, message);
            // Need to send a message to the clients in the lobby to tell them there a new player
        }
        if (owner.msg.header.header_id == Network::GET_LOBBY_LIST) {
            Network::Message<Network::Codes> message;
            message.header.header_id = Network::LOBBY_LIST;
            for (const auto &[uuid, lobby] : _listLobby) {
                message << lobby->getNumberPlayers() << lobby->getUuid();
            }
            _server->send(owner.client, message);
        }
		if (owner.msg.header.header_id == Network::INPUT_TCHAT) {
			char c;

            while (owner.msg.body.size() > 0)
            {
                owner.msg >> c;
			    _chatMessage += c;
            }

            std::reverse(_chatMessage.begin(), _chatMessage.end());
            sendChatMessage(owner);
		}
        _msgList->pop();
    }
}

void Server::ManageLobby::sendChatMessage(CommandOwnedMsg owner)
{
    Network::Message<Network::Codes> msg;
    msg.header.header_id = Network::TCHAT;

    for (int i = 0; i < _chatMessage.length(); i++) {
        msg << _chatMessage[i];
    }
    std::function<void(const uint32_t &)> empty = [](const uint32_t &t){};
	_server->notifiyClients(msg, empty);
    _chatMessage.clear();
}

void Server::ManageLobby::manageLobby()
{}

void Server::ManageLobby::run()
{
	_server->start();
    while (!stop) {
		readProcessMessages();
        getMessages();
        manageLobby();
    }
}