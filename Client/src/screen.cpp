/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** screen
*/

#include "../include/screen.hpp"


Screen::Screen(const uint16_t &screenWidth, const uint16_t &screenHeight, std::shared_ptr<Network::Client<Network::Codes>> &client)
: _screenWidth(screenWidth), _screenHeight(screenHeight), _client(client)
{
}

void Screen::initWindow()
{
    InitWindow(_screenWidth, _screenHeight, "R-Type");
    InitAudioDevice();

    SetTargetFPS(60);
    _mousePoint = { 0.0f, 0.0f };

}

void Screen::setMenuTextures()
{

    _soundManager = SoundManager();

    _background.createBackground("asset/BG/BG_2_PlanetCorner.png");
    _background2.createBackground("asset/BG/BG_2_StarsBG2.png");
    _background3.createBackground("asset/BG/BG_2_StarsBG2.png");
    _playButton.setTextureButton("asset/Button/play.png");
    _settingButton.setTextureButton("asset/Button/settingbutton.png");
    _lobbyButton.setTextureButton("asset/Button/creatlobby.png");
    _listLobbyButton.setTextureButton("asset/Button/joinlobby.png");
    _lobbyBackground.createBackground("asset/interfaceLobby.png");
    _slotBackground.createBackground("asset/buttonplayerasset.png");
    _joinLobbyButton.setTextureButton("asset/Button/playbutton.png");
    _rtypeLogo.createBackground("asset/Rtype.png");
    _changeSkinPlayer.setTextureButton("asset/Button/buttochangeplayer.png");
    _changeSkinEnemies.setTextureButton("asset/Button/buttonchangeenemies.png");
    _rightArrow.setTextureButton("asset/Button/right.png");
    _leftArrow.setTextureButton("asset/Button/left.png");
    _saveButton.setTextureButton("asset/Button/save.png");
    _spaceShip1.createBackground("asset/spaceship.png");
    _spaceShip2.createBackground("asset/spaceship2.png");
    _spaceShip3.createBackground("asset/spaceship3.png");
    _spaceShip4.createBackground("asset/spaceship4.png");
    _enemy1.createBackground("asset/enemy1.png");
    _enemy2.createBackground("asset/enemy2.png");
    _enemy3.createBackground("asset/enemy3.png");
    _enemy4.createBackground("asset/enemy4.png");
    _spaceShipSkin = "asset/spaceship.png";
    _enemySkin = "asset/enemy1.png";
	_leaveButton.setTextureButton("asset/Button/buttonleave.png");
    _chatBox.setTextureButton("asset/Button/chatbox.png");
    _plusButton.setTextureButton("asset/Button/buttonplus.png");
    _minusButton.setTextureButton("asset/Button/buttonmoins.png");

    _playButton._size = 1;
    _settingButton._size = 0.25;
	_leaveButton._size = 1;
    _plusButton._size = 0.25;
    _minusButton._size = 0.25;
    _chatBox._size = 1;
    _joinLobbyButton._size = 0.25;  
    _changeSkinPlayer._size = 0.75;
    _changeSkinEnemies._size = 0.75;
    _rightArrow._size = 0.25;
    _leftArrow._size = 0.25;
    _saveButton._size = 0.25;
    _PName.setFontSize(50);
    _PName.setFontColor(WHITE);
    _TChat.setFontSize(15);
    _TChat.setFontColor(WHITE);
    _TChat.setposText(1325, 175);
    _VolumeTitle.setFontSize(50);
    _VolumeTitle.setFontColor(WHITE);
    _VolumeTitle.setposText(_screenWidth / 2 - 70, _screenHeight / 2 - 350);
    _VolumeValue.setFontSize(50);
    _VolumeValue.setFontColor(WHITE);
    _VolumeValue.setposText(_screenWidth / 2 + 30, _screenHeight / 2 - 280);
    _Score.setFontSize(50);
    _Score.setFontColor(WHITE);
    _Score.setposText(_screenWidth / 2 + 600, _screenHeight / 2 - 500);
    _WaveNbr.setFontSize(50);
    _WaveNbr.setFontColor(WHITE);
    _WaveNbr.setposText(_screenWidth / 2 + 600, _screenHeight / 2 - 400);
    
}

void Screen::mainMenu()
{
    currentScreen = MENU;

    _playButton.setposButton(_screenWidth/2 - 280, _screenHeight/2 - 200);
    _settingButton.setposButton(_screenWidth/2 - 900, _screenHeight/2 - 500);
    _lobbyButton.setposButton(_screenWidth/2 - 250, _screenHeight/2 - 300);
    _listLobbyButton.setposButton(_screenWidth/2 - 250, _screenHeight/2);
    _background3.setposBackground(_background2.getBackground().width, 0);
    _rtypeLogo.setposBackground(_screenWidth/2 - 500, _screenHeight/2 - 500);
    _lobbyBackground.setposBackground(100, 100);
    _chatBox.setposButton(1300, 600);
    _changeSkinPlayer.setposButton(_screenWidth / 2 + 100, _screenHeight / 2 - 100);
    _changeSkinEnemies.setposButton(_screenWidth / 2 - 400, _screenHeight / 2 - 100);
    _rightArrow.setposButton(_screenWidth / 2 + 880, _screenHeight / 2 - 100);
    _leftArrow.setposButton(_screenWidth / 2 - 950, _screenHeight / 2 - 100);
    _saveButton.setposButton(_screenWidth / 2 - 900, _screenHeight / 2 + 300);
    _plusButton.setposButton(_screenWidth / 2 - 150, _screenHeight / 2 - 300);
    _minusButton.setposButton(_screenWidth / 2 + 100, _screenHeight / 2 - 300);

    _btnBounds = {_playButton.getposButton().x, _playButton.getposButton().y, (float)_playButton.getTextureButton().width, (float)_playButton.getTextureButton().height};
    _btnBounds2 = {_lobbyButton.getposButton().x, _lobbyButton.getposButton().y, (float)_lobbyButton.getTextureButton().width, (float)_lobbyButton.getTextureButton().height};
    _btnBounds3 = {_listLobbyButton.getposButton().x, _listLobbyButton.getposButton().y, (float)_listLobbyButton.getTextureButton().width, (float)_listLobbyButton.getTextureButton().height};
	_btnLeaveBounds = {_leaveButton.getposButton().x, _leaveButton.getposButton().y, (float)_leaveButton.getTextureButton().width, (float)_leaveButton.getTextureButton().height};
    _btnSettingBounds = {_settingButton.getposButton().x, _settingButton.getposButton().y, ((float)_settingButton.getTextureButton().width * (float)0.25), ((float)_settingButton.getTextureButton().height * (float)0.25)};
    _btnChangeSkinPlayer = {_changeSkinPlayer.getposButton().x, _changeSkinPlayer.getposButton().y, ((float)_changeSkinPlayer.getTextureButton().width * (float)0.75), ((float)_changeSkinPlayer.getTextureButton().height * (float)0.75)};
    _btnChangeSkinEnemies = {_changeSkinEnemies.getposButton().x, _changeSkinEnemies.getposButton().y, ((float)_changeSkinEnemies.getTextureButton().width * (float)0.75), ((float)_changeSkinEnemies.getTextureButton().height * (float)0.75)};
    _btnRightArrow = {_rightArrow.getposButton().x, _rightArrow.getposButton().y, ((float)_rightArrow.getTextureButton().width * (float)0.25), ((float)_rightArrow.getTextureButton().height * (float)0.25)};
    _btnLeftArrow = {_leftArrow.getposButton().x, _leftArrow.getposButton().y, ((float)_leftArrow.getTextureButton().width * (float)0.25), ((float)_leftArrow.getTextureButton().height * (float)0.25)};
    _btnSaveButton = {_saveButton.getposButton().x, _saveButton.getposButton().y, ((float)_saveButton.getTextureButton().width * (float)0.25), ((float)_saveButton.getTextureButton().height * (float)0.25)};
    _btnPlusButton = {_plusButton.getposButton().x, _plusButton.getposButton().y, ((float)_plusButton.getTextureButton().width * (float)0.25), ((float)_plusButton.getTextureButton().height * (float)0.25)};
    _btnMinusButton = {_minusButton.getposButton().x, _minusButton.getposButton().y, ((float)_minusButton.getTextureButton().width * (float)0.25), ((float)_minusButton.getTextureButton().height * (float)0.25)};
}

void Screen::mainMenuAction()
{
    _soundManager.MusicLobby.playMusic();
    _mousePoint = GetMousePosition();
	if (CheckCollisionPointRec(_mousePoint, _btnBounds)){
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            _soundManager.ButtonSound.playSound();
			currentScreen = LOBBY;
			Network::Message<Network::Codes> msg;
			msg.header.header_id = Network::GET_LOBBY_LIST;
			_client->send_message(msg);
		}
	}
    if (CheckCollisionPointRec(_mousePoint, _btnSettingBounds)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = SETTING;
        }
    }
}

void Screen::DrawSettingMenu()
{
    _soundManager.MusicLobby.updateMusicStream();
    DrawParallax();
    _changeSkinPlayer.drawButton();
    _changeSkinEnemies.drawButton();
    _settingButton.drawButton();
    _plusButton.drawButton();
    _minusButton.drawButton();
    _VolumeTitle.setText("Volume");
    _VolumeTitle.drawText();
    std::string volume = std::to_string(_soundManager._volume * 10).erase(std::to_string(_soundManager._volume).find_first_not_of('0') + 1, std::string::npos);
    if (volume.back() == '.')
        volume.pop_back();
    _VolumeValue.setText(volume);
    _VolumeValue.drawText();
}

void Screen::settingMenuActions() {
    _mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(_mousePoint, _btnChangeSkinPlayer)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = CHANGEPLAYER;
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnChangeSkinEnemies)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = CHANGEENEMIES;
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnSettingBounds)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = MENU;
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnPlusButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_soundManager._volume < 0.9f)
                _soundManager.changeVolume(_soundManager._volume + 0.1f);
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnMinusButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_soundManager._volume > 0.1f)
                _soundManager.changeVolume(_soundManager._volume - 0.1f);
        }
    }
}

void Screen::changeEnemiesMenuActions() {
    _mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(_mousePoint, _btnRightArrow)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin < 3) {
                _currentSkin++;
            }
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnLeftArrow)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin > 0) {
                _currentSkin--;
            }
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnSettingBounds)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = SETTING;
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnSaveButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin == 0) {
                _enemySkin = "asset/enemy1.png";
            }
            else if (_currentSkin == 1) {
                _enemySkin = "asset/enemy2.png";
            }
            else if (_currentSkin == 2) {
                _enemySkin = "asset/enemy3.png";
            }
            else if (_currentSkin == 3) {
                _enemySkin = "asset/enemy4.png";
            }
            currentScreen = SETTING;
        }
    }
}

void Screen::changePlayerMenuActions() {
    _mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(_mousePoint, _btnRightArrow)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin < 3) {
                _currentSkin++;
            }
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnLeftArrow)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin > 0) {
                _currentSkin--;
            }
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnSettingBounds)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            currentScreen = SETTING;
        }
    }
    if (CheckCollisionPointRec(_mousePoint, _btnSaveButton)) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            _soundManager.ButtonSound.playSound();
            if (_currentSkin == 0) {
                _spaceShipSkin = "asset/spaceship.png";
            } else if (_currentSkin == 1) {
                _spaceShipSkin = "asset/spaceship2.png";
            } else if (_currentSkin == 2) {
                _spaceShipSkin = "asset/spaceship3.png";
            } else if (_currentSkin == 3) {
                _spaceShipSkin = "asset/spaceship4.png";
            }
            currentScreen = SETTING;
        }
    }
}

void Screen::DrawChangeEnemiesMenu()
{
    _soundManager.MusicLobby.updateMusicStream();
    DrawParallax();
    _rightArrow.drawButton();
    _leftArrow.drawButton();
    _settingButton.drawButton();
    _saveButton.drawButton();
    if (_currentSkin == 0) {
        _enemy1.setScale(0.75);
        _enemy1.setposBackground(_screenWidth / 2 - 400, _screenHeight / 2 - 200);
        _enemy1.setposBackground(_enemy1._pos.x, _enemy1._pos.y + sinf(GetTime() * 2) * 20);
        _enemy1.drawBackground();
    } else if (_currentSkin == 1) {
        _enemy2.setScale(0.75);
        _enemy2.setposBackground(_screenWidth / 2 - 400, _screenHeight / 2 - 200);
        _enemy2.setposBackground(_enemy2._pos.x, _enemy2._pos.y + sinf(GetTime() * 2) * 20);
        _enemy2.drawBackground();
    } else if (_currentSkin == 2) {
        _enemy3.setScale(0.75);
        _enemy3.setposBackground(_screenWidth / 2 - 400, _screenHeight / 2 - 200);
        _enemy3.setposBackground(_enemy3._pos.x, _enemy3._pos.y + sinf(GetTime() * 2) * 20);
        _enemy3.drawBackground();
    } else if (_currentSkin == 3) {
        _enemy4.setScale(0.75);
        _enemy4.setposBackground(_screenWidth / 2 - 400, _screenHeight / 2 - 200);
        _enemy4.setposBackground(_enemy4._pos.x, _enemy4._pos.y + sinf(GetTime() * 2) * 20);
        _enemy4.drawBackground();
    }
}

void Screen::DrawChangePlayerMenu()
{
    _soundManager.MusicLobby.updateMusicStream();
    DrawParallax();
    _rightArrow.drawButton();
    _leftArrow.drawButton();
    _settingButton.drawButton();
    _saveButton.drawButton();
    if (_currentSkin == 0) {
        _spaceShip1.setScale(1.25);
        _spaceShip1.setposBackground(_screenWidth / 2 - 400, _screenHeight / 2 - 300);
        _spaceShip1.setposBackground(_spaceShip1._pos.x, _spaceShip1._pos.y + sinf(GetTime() * 2) * 20);
        _spaceShip1.drawBackground();
    } else if (_currentSkin == 1) {
        _spaceShip2.setScale(1.25);
        _spaceShip2.setposBackground(_screenWidth / 2 - 450, _screenHeight / 2 - 200);
        _spaceShip2.setposBackground(_spaceShip2._pos.x, _spaceShip2._pos.y + sinf(GetTime() * 2) * 20);
        _spaceShip2.drawBackground();
    } else if (_currentSkin == 2) {
        _spaceShip3.setScale(1.25);
        _spaceShip3.setposBackground(_screenWidth / 2 - 300, _screenHeight / 2 - 350);
        _spaceShip3.setposBackground(_spaceShip3._pos.x, _spaceShip3._pos.y + sinf(GetTime() * 2) * 20);
        _spaceShip3.drawBackground();
    } else if (_currentSkin == 3) {
        _spaceShip4.setScale(1.25);
        _spaceShip4.setposBackground(_screenWidth / 2 - 330, _screenHeight / 2 - 220);
        _spaceShip4.setposBackground(_spaceShip4._pos.x, _spaceShip4._pos.y + sinf(GetTime() * 2) * 20);
        _spaceShip4.drawBackground();
    }
}


void Screen::DrawParallax()
{
    ClearBackground(BLACK);
    _background2.drawBackground();
    _background.drawBackground();
    _background3.drawBackground();
    _background2.moveBackground();
    _background3.moveBackground();
}

void Screen::DrawMainMenu()
{
    _soundManager.MusicLobby.updateMusicStream();
    _playButton.drawButton();
    _settingButton.drawButton();
    DrawParallax();
    _rtypeLogo.setScale(2.0);
    _rtypeLogo.drawBackground();
}

void Screen::DrawGame()
{
    if (_isPlaying == false) {
        _soundManager.StartGameSound.playSound();
        _isPlaying = true;
    }
    _soundManager.MusicGameplay.playMusic();
    _soundManager.MusicGameplay.updateMusicStream();
    DrawParallax();
    if (IsKeyReleased(KEY_SPACE)) {
        _soundManager.BulletSound.playSound();
    }
    _Score.setText("Score : " + std::to_string(_client->getScore()));
    _Score.drawText();
    _WaveNbr.setText("Wave : " + std::to_string(_client->getWaveNbr()));
    _WaveNbr.drawText();
}

void Screen::lobbyMenu()
{
    _mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(_mousePoint, _btnBounds2)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                _soundManager.ButtonSound.playSound();
                currentScreen = CREATELOBBY;
				Network::Message<Network::Codes> msg;
				msg.header.header_id = Network::CREATE_LOBBY;
				_client->send_message(msg);
            }
        }
        if (CheckCollisionPointRec(_mousePoint, _btnBounds3)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                _soundManager.ButtonSound.playSound();
                currentScreen = JOINLOBBY;
            }
        }
}

void Screen::DrawLobbyMenu()
{
    _soundManager.MusicLobby.updateMusicStream();
    DrawParallax();
    _lobbyButton._size = 1;
    _lobbyButton.drawButton();
    _listLobbyButton._size = 1;
    _listLobbyButton.drawButton();
}

void Screen::createLobbyMenu()
{
    _mousePoint = GetMousePosition();
        if (CheckCollisionPointRec(_mousePoint, _btnBounds3)){
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                currentScreen = GAMEPLAY;
            }
        }
}

void Screen::DrawCreateLobbyMenu(const std::vector<uint32_t> &_playerIDList, const std::vector<std::string> &TChatList)
{
    _chatFeed = TChatList;
    std::string output = "";
    int x = 150;
    int y = 150;

    DrawParallax();
    _soundManager.MusicLobby.updateMusicStream();
    _lobbyBackground.drawBackground();

    for (int i = 0; i < _playerIDList.size(); i++){
        output.clear();
        std::string strPlayerName = std::to_string(_playerIDList[i]);
        for (int i = 0; i < strPlayerName.length(); i++) {
            output += strPlayerName[i];
            if (i != strPlayerName.length() - 1) {
                output += " ";
            }
        }
        _PName.setText(output);

        _slotBackground.setposBackground(x, y);
        _slotBackground.drawBackground();
        _PName.setposText(x + 60, y + 80);
        _PName.drawText();
        y += 150;
    }

    _playButton.setposButton(1350, 800 - _playButton.getTextureButton().height/2);
    _playButton.drawButton();
    _btnBounds = {_playButton.getposButton().x, _playButton.getposButton().y, (float)_playButton.getTextureButton().width, (float)_playButton.getTextureButton().height};
	_leaveButton.drawButton();
    LobbyChat();
    CreateLobbyMenuAction();
}

void Screen::LobbyChat()
{
    std::string line = "";
    std::string printChat = "";
    int y = 175;

    _TChat.setFontSize(30);

    for (int i = 0; i < _chatFeed.size(); i++)
    {
        line = _chatFeed[i];
        for (int i = 0; i < line.length(); i++) {
            printChat += line[i];
            if (i != line.length() - 1) {
                printChat += " ";
            }
        }
        _TChat.setposText(1325, y);
        _TChat.setText(printChat);
        _TChat.drawText();
        y += 50;
        printChat.clear();
    }


    printChat.clear();
    for (int i = 0; i < _inputText.length(); i++) {
        printChat += _inputText[i];
        if (i != _inputText.length() - 1) {
            printChat += " ";
        }
    }

    //! Max 105 char for display (including spaces)

    _chatBox.drawButton();
    _TChat.setFontSize(25);
    _TChat.setposText(1350, 630);
    _TChat.setText(printChat);
    _TChat.drawText();
}

void Screen::sendChatMessage()
{
    Network::Message<Network::Codes> msg;
    msg.header.header_id = Network::INPUT_TCHAT;
    for (int i = 0; i < _inputText.length(); i++) {
        msg << _inputText[i];
    }
    _client->send_message(msg);
}

void Screen::chatInput()
{
        if (IsKeyPressed(KEY_BACKSPACE) && _inputText.length() > 0) {
        _inputText.pop_back();
    }
    else if (IsKeyPressed(KEY_ENTER) && _inputText.length() > 0) {
        sendChatMessage();
        _inputText.clear();
    }
    else {
        char key = GetKeyPressed();
        if (key != '\0' && _inputText.length() < 20) {
            _inputText += key;
        }
    }
}

void Screen::CreateLobbyMenuAction()
{
    _mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(_mousePoint, _btnBounds)){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
			Network::Message<Network::Codes> msg;
			msg.header.header_id = Network::START_GAME;
			_client->send_data(msg);
            currentScreen = GAMEPLAY;
        }
    }
	if (CheckCollisionPointRec(_mousePoint, _btnLeaveBounds)){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
			Network::Message<Network::Codes> msg;
			msg << _client->getId();
			msg.header.header_id = Network::LEAVE;
			_client->send_data(msg);
            currentScreen = LOBBY;
        }
    }
}

void Screen::joinLobbyMenu()
{
    if (CheckCollisionPointRec(_mousePoint, _btnBounds3)){
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            currentScreen = JOINLOBBY;
        }
    }
}

void Screen::drawJoinLobbyMenu(const std::vector<std::tuple<int, uint32_t>> &listLobby)
{
    _soundManager.MusicLobby.updateMusicStream();
    _mousePoint = GetMousePosition();
    std::vector<Rectangle> lobbyBounds;
    std::string strLobbyName;
    std::string output;
    GameEngine::Text lobbyName;
    lobbyName.setFontSize(50);
    lobbyName.setFontColor(WHITE);
    int x = 210;
    int y = 230;

    DrawParallax();
    _lobbyBackground.drawBackground();

    for (const auto &[nbPlayers, lobbyId] : listLobby) {
        Rectangle joinButtonBounds;
        _joinLobbyButton.setposButton(820, y - 5);
        joinButtonBounds = {_joinLobbyButton.getposButton().x, _joinLobbyButton.getposButton().y, ((float)_joinLobbyButton.getTextureButton().width * (float)0.25), ((float)_joinLobbyButton.getTextureButton().height * (float)0.25)};
        lobbyBounds.push_back(joinButtonBounds);
        strLobbyName.clear();
        output.clear();
        _slotBackground.setposBackground(150, y - 80);
        strLobbyName = std::to_string(lobbyId);
        for (int i = 0; i < strLobbyName.length(); i++) {
            output += strLobbyName[i];
            if (i != strLobbyName.length() - 1) {
                output += " ";
            }
        }

        strLobbyName = " ( " + std::to_string(nbPlayers) + "/4 )  -  " + output;
        lobbyName.setText(strLobbyName);
        lobbyName.setposText(x, y);
        _slotBackground.drawBackground();
        lobbyName.drawText();
        _joinLobbyButton.drawButton();
        y += 150;
    }
    joinLobbyMenuActions(lobbyBounds, listLobby);
}

void Screen::joinLobbyMenuActions(const std::vector<Rectangle> &lobbyBounds, const std::vector<std::tuple<int, uint32_t>> &listLobby)
{
    int i = 0;
    uint32_t lobbyId = 0;

        for (const auto &bounds : lobbyBounds) {
            if (CheckCollisionPointRec(_mousePoint, bounds)) {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) || IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                    std::cout << "JOIN LOBBY" << std::endl;
                    lobbyId = std::get<1>(listLobby[i]);
                    std::cout << "lobbyId = " << lobbyId << std::endl;
                    Network::Message<Network::Codes> msg;
                    msg.header.header_id = Network::JOIN_LOBBY;
                    msg << lobbyId;
                    _client->send_message(msg);
                    currentScreen = CREATELOBBY;
                }
            }
        i++;
    }

}

void Screen::DrawEntities(std::unique_ptr<GameEngine::EntityManager> &entities)
{
    for (auto &ptr : entities->getEntityList())
    {
        DrawTextureEx(ptr->getComp<GameEngine::Style>()->_texture, ptr->getComp<GameEngine::Position>()->getPosition(), 0.0, 0.25, WHITE);
    }
}

void Screen::DestroyEntities(std::unique_ptr<GameEngine::EntityManager> &entities)
{
    for (auto &ptr : entities->getEntityList())
    {
        UnloadTexture(ptr->getComp<GameEngine::Style>()->_texture);
    }

    _background.destroy();
	_background2.destroy();
	_background3.destroy();

	_playButton.destroy();
    _lobbyButton. destroy();
    _listLobbyButton. destroy();
    _lobbyBackground. destroy();
    _slotBackground. destroy();
    _joinLobbyButton. destroy();
}

Screen::~Screen()
{
}
