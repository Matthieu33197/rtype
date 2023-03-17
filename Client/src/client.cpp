/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Client.cpp
*/

#include "../include/client.hpp"
#include "../include/vector.hpp"

Game::Client::Client(const std::string &host, const unsigned short int &port)
: _client(std::make_shared<Network::Client<Network::Codes>>(host, port)), _TChat(""), _preLoaded(false)
{
	_screen = Screen(1920, 1080, _client);
	_cmds[Network::ID_PLAYER] = [=, this](CombOwnedMsg &owner) {
		return setID(owner);
    };
    _cmds[Network::LOBBY_PORT] = [=, this](CombOwnedMsg &owner) {
      return connectData(owner);
    };
    _cmds[Network::POS] = [=, this](CombOwnedMsg &owner) {
      return _entityHandler.moveEntity(owner);
    };
    _cmds[Network::UPDATE_ENTITIES] = [=, this](CombOwnedMsg &owner) {
      return _entityHandler.updateEntity(owner);
    };
    _cmds[Network::UNLOAD_ENTITY] = [=, this](CombOwnedMsg &owner) {
      return _entityHandler.removeEntity(owner);
    };
	_cmds[Network::LOBBY_LIST] = [=, this](CombOwnedMsg &owner) {
		return saveLobbyList(owner);
	};
	_cmds[Network::PLAYER_LIST_LOBBY] = [=, this](CombOwnedMsg &owner) {
		return savePlayerList(owner);
	};
	_cmds[Network::TCHAT] = [=, this](CombOwnedMsg &owner) {
		return saveTChat(owner);
	};
	_cmds[Network::SCORE] = [=, this](CombOwnedMsg &owner) {
		return updateScore(owner);
	};
	_cmds[Network::WAVENBR] = [=, this](CombOwnedMsg &owner) {
		return updateWaveNumber(owner);
	};
}

int Game::Client::updateWaveNumber(CombOwnedMsg &owner)
{
	if (owner.msg.body.size() == sizeof(uint32_t)) {
		owner.msg >> _waveNbr;
		_client->setWaveNbr(_waveNbr);
	}
	return 0;
}

int Game::Client::updateScore(CombOwnedMsg &owner)
{
	if (owner.msg.body.size() == sizeof(uint32_t)) {
		owner.msg >> _score;
		_client->setScore(_score);
	}
	return 0;
}

int Game::Client::setID(CombOwnedMsg &owner)
{
	if (owner.msg.body.size() == sizeof(uint32_t)) {
		owner.msg >> id;
		_client->setId(id);
	}
	return 0;
}

int Game::Client::savePlayerList(CombOwnedMsg &owner)
{
	if (!(owner.msg.body.size() % sizeof(uint32_t))) {
		_playerIDList.clear();
		uint32_t id = 0;
		while (owner.msg.body.size()) {
			owner.msg >> id;
			_playerIDList.push_back(id);
		}
	}
	return 0;
}

int Game::Client::saveTChat(CombOwnedMsg &owner)
{
	char c = 0;

    while (owner.msg.body.size() > 0)
    {
        owner.msg >> c;
	    _TChat += c;
    }
    std::reverse(_TChat.begin(), _TChat.end());
	_TChat += '\0';
	_TChatList.push_back(_TChat);
	_TChat.clear();

	if (_TChatList.size() == 10)
        _TChatList.erase(_TChatList.begin());

	return 0;
}

int Game::Client::saveLobbyList(CombOwnedMsg &owner)
{
	if (!(owner.msg.body.size() % (sizeof(int) + sizeof(uint32_t)))) {
		_lobbyList.clear();
		int nbPlayers = 0;
		uint32_t  lobyId = 0;
		while (owner.msg.body.size()) {
			owner.msg >> lobyId;
			owner.msg >> nbPlayers;
			_lobbyList.push_back(std::make_tuple(nbPlayers, lobyId));
		}
	}
	return 0;
}

int Game::Client::connectData(CombOwnedMsg &owner)
{
	uint16_t port = 0;

	if (owner.msg.body.size() == sizeof(uint16_t)) {
		owner.msg >> port;
		_client->connectData("127.0.0.1", static_cast<unsigned short int>(port));
		_msg.header.header_id = Network::Codes::HELLO_LOBBY;
		_msg << id;
		_client->send_data(_msg);
		_msg.body.clear();
	}
	return 0;
}

void Game::Client::checkMessages()
{
	CombOwnedMsg msg;

	while (!_msgList->isEmpty()) {
		msg = _msgList->front();
		if (!(_cmds.find(msg.msg.header.header_id) == _cmds.end()))
			_cmds[msg.msg.header.header_id](msg);
		else
			std::cerr << "[Error]: unkown command: " << _msg.header.header_id << std::endl;
		_msgList->pop();
	}
}

int Game::Client::start()
{
    // Check if client can successfully connects to server
	if (_client->connect() == -1)
		return 84;
	_msg.header.header_id = Network::HELLO_TCP;
	_msgList = _client->get_received_msg();
	_client->send_message(_msg);
    // Initialize the window
    _screen.initWindow();
	_screen.setMenuTextures();

	// Initializint assets for the main menu
	_screen.mainMenu();
	// Main game loop
	run();
    // Manually unload the entities
	return 0;
}

void Game::Client::getInput()
{
	int key = GetKeyPressed();

	if (IsKeyDown(KEY_RIGHT)) {
		int8_t direction = static_cast<int8_t>(GameEngine::MOVE_RIGHT);
		_msg.header.header_id = Network::Codes::MOVE;
		_msg << id << direction;
		_client->send_data(_msg);
		_msg.body.clear();
	} else if (IsKeyDown(KEY_LEFT)) {
		int8_t direction = static_cast<int8_t>(GameEngine::MOVE_LEFT);
		_msg.header.header_id = Network::Codes::MOVE;
		_msg << id << direction;
		_client->send_data(_msg);
		_msg.body.clear();
	} else if (IsKeyDown(KEY_DOWN)) {
		int8_t direction = static_cast<int8_t>(GameEngine::MOVE_DOWN);
		_msg.header.header_id = Network::Codes::MOVE;
		_msg << id << direction;
		_client->send_data(_msg);
		_msg.body.clear();
	} else if (IsKeyDown(KEY_UP)) {
		int8_t direction = static_cast<int8_t>(GameEngine::MOVE_UP);
		_msg.header.header_id = Network::Codes::MOVE;
		_msg << id << direction;
		_client->send_data(_msg);
		_msg.body.clear();
	}
	if (IsKeyReleased(KEY_SPACE)) {
		sendPlayerShoot();
	}
}

void Game::Client::sendPlayerShoot()
{
    uint32_t entity_id = id;
	_msg.header.header_id = Network::Codes::SHOOT;
	_msg << entity_id;
	_client->send_data(_msg);
	_msg.body.clear();
}

void Game::Client::run()
{
	checkMessages();
	while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        switch(_screen.currentScreen)
        {
            case GameScreen::MENU:
            {
                _screen.mainMenuAction();    // Actions related to the main menu
            } break;
            case GameScreen::GAMEPLAY:
            {
            } break;
			case GameScreen::LOBBY:
			{
				_screen.lobbyMenu();
			} break;
			case GameScreen::CREATELOBBY:
			{
				if (_preLoaded == false) {
					_entityHandler.preLoadTextures(_screen._spaceShipSkin, _screen._enemySkin);
					_preLoaded = true;
				}
				_screen.createLobbyMenu();
				_screen.chatInput();
			} break;
            case GameScreen::JOINLOBBY:
            {
                _screen.joinLobbyMenu();
            } break;
			case GameScreen::SETTINGS:
			{
				_screen.settingMenuActions();
			} break;
			case GameScreen::CHANGEPLAYER:
			{
				_screen.changePlayerMenuActions();
			} break;
			case GameScreen::CHANGEENEMIES:
			{
				_screen.changeEnemiesMenuActions();
			} break;
            default: break;
        }
		checkMessages();
		getInput();
		display();
    }
}

void Game::Client::display()
{
	BeginDrawing();
		ClearBackground(RAYWHITE);
		switch(_screen.currentScreen)
		{
			case GameScreen::MENU:
			{
				_screen.DrawMainMenu();
			} break;
			case GameScreen::GAMEPLAY:
			{
				_screen.DrawGame();
				_screen.DrawEntities(_entityHandler.getEntities());
			} break;
			case GameScreen::LOBBY:
			{
				_screen.DrawLobbyMenu();
			} break;
			case GameScreen::CREATELOBBY:
			{
				_screen.DrawCreateLobbyMenu(_playerIDList, _TChatList);
			} break;
            case GameScreen::JOINLOBBY:
            {
                _screen.drawJoinLobbyMenu(_lobbyList);
            } break;
			case GameScreen::SETTINGS:
			{
				_screen.DrawSettingMenu();
			} break;
			case GameScreen::CHANGEPLAYER:
			{
				_screen.DrawChangePlayerMenu();
			} break;
			case GameScreen::CHANGEENEMIES:
			{
				_screen.DrawChangeEnemiesMenu();
			} break;
			default: break;
		}
	EndDrawing();
}

Game::Client::~Client()
{
	_client->disconnect();
	_screen.DestroyEntities(_entityHandler.getEntities());
    CloseWindow();
}
