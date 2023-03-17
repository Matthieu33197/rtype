/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Screen.hpp
*/

#ifndef R_TYPE_SCREEN_HPP
#define R_TYPE_SCREEN_HPP

#include <iostream>
#include "raylib.h"
#include "soundManager.hpp"
#include "../../Lib/GameEngine/include/Utils/Background.hpp"
#include "../../Lib/GameEngine/include/Utils/Button.hpp"
#include "../../Lib/Network/include/client_interface.hpp"
#include "../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../Lib/GameEngine/include/Components/Style.hpp"
#include "../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../Lib/GameEngine/include/Utils/Text.hpp"
#include "../../Lib/Network/include/client_interface.hpp"
#include "../../include/NetworkAlias.hpp"
#include "../../Lib/GameEngine/include/Utils/Musics.hpp"
#include "../../Lib/GameEngine/include/Utils/Sounds.hpp"

typedef enum GameScreen {
	MENU, GAMEPLAY, LOBBY, CREATELOBBY, JOINLOBBY, SETTINGS, CHANGEPLAYER, CHANGEENEMIES
} GameScreen;

class Screen {
    public:
		Screen() = default;
        //! Screen constructor
        /*
        * Constructur that takes two usnigned 16 bits numbers as parameters.
        @param screenWidth: desired screen's width.
        @param screenHeight: desired screen's height.
        */
        Screen(const uint16_t &screenWidth, const uint16_t &screenHeight,
				std::shared_ptr<Network::Client<Network::Codes>> &client);
        //! Screen destructor
        /*
         The distructor calls all the elements that need to be unloaded.
        */
        ~Screen();
        //! Window initializer
        /*
         Creates the window with the desired width and height.
         It also sets the framerate to 60 and sets a default mouse position.
        */
        void initWindow();
        //! Main menu initializer
        /*
         Sets / loads evrything required for the main menu.
        */
        void mainMenu();
        //! Main menu actions
        /*
         Checks for different interactions with the main menu.
        */
        void mainMenuAction();
        //! Main menu drawer
        /*
         Draws all the assets for the main menu
        */
        void DrawMainMenu();
        //! Lobby actions
        /*
         Checks for different interactions with the lobby.
        */
        void lobbyMenu();
        //! Lobby drawer
        /*
         Draws all the assets for the lobby.
        */
        void DrawLobbyMenu();
        void createLobbyMenu();
        //! Create lobby creator
        /*
         Draws all the assets for the create lobby screen.
        */
        void DrawCreateLobbyMenu(const std::vector<uint32_t> &_playerIDList, const std::vector<std::string> &TChatList);
        //! Menu textures setter
        /*
         Loads and sets all the needed textures for the menu.
        */
        void setMenuTextures();
        //! Parallax drawer
        /*
        Draws the parallax in the background
        */
        void DrawParallax();
        //! Settings menu
        /*
        Draws the necessary assets for the settings menu
        */
        void DrawSettingMenu();
        //! Settings menu
        /*
         Loads and sets all the needed textures for the menu.
        */
        void settingMenuActions();
        //! Player skin selection menu actions
        /*
         Computes the required actions for  the player's skin selection menu
        */
        void changePlayerMenuActions();
        //! Enemy skin selection menu actions
        /*
         Computes the required actions for  the enemy's skin selection menu
        */
        void changeEnemiesMenuActions();
        //! Player skin selection menu drawer
        /*
         Draws the required actions for  the player's skin selection menu
        */
        void DrawChangePlayerMenu();
        //! Enemy skin selection menu drawer
        /*
         Draws the required actions for  the enemy's skin selection menu
        */
        void DrawChangeEnemiesMenu();
        //!Send input chat field
        /*
         Sends the input chat field to the server
        */
        void sendChatMessage();
        //! Game Drawer
        /*
         When called, it draws all the assets for the game.
        */
        void DrawGame();
        //! SetEntityTextures function
        /*!
         The function sets all the entity's texture
		 @param entities list of all the entities
       	*/
        void SetEntityTextures(std::unique_ptr<GameEngine::EntityManager> &entities);
        //! DrawEntities function
        /*!
         The function draw's all the entities
		 @param entities list of all the entities
       	*/
        void DrawEntities(std::unique_ptr<GameEngine::EntityManager> &entities);
        //! DestroyEntities function
        /*!
         The function unload's all the entities
		 @param entities list of all the entities
       	*/
        void DestroyEntities(std::unique_ptr<GameEngine::EntityManager> &entities);
        //! join lobby button
        /*
         Check's if the player click on the join lobby button
        */
        void joinLobbyMenu();
        //! Join lobby menu drawer
        /*
         Draws the required elements for the join lobby menu
        */
        void drawJoinLobbyMenu(const std::vector<std::tuple<int, uint32_t>> &listLobby);
        //! Join lobby menu actions
        /*
         Actions for the join lobby menu
        */
        void joinLobbyMenuActions(const std::vector<Rectangle> &lobbyBounds, const std::vector<std::tuple<int, uint32_t>> &listLobby);
        //! Create lobby menu actions
        /*
         Actions for the create lobby menu
        */
        void CreateLobbyMenuAction();
        //! Lobby chat Handler
        /*
         Displays the chat feed in the lobby
        */
        void LobbyChat();
        //! Input box for the chat
        /*
         Displays the input box where the player can view the message before it is sent to the server
        */
        void chatInput();
        std::string _spaceShipSkin;
        std::string _enemySkin;
        typedef enum GameScreen {MENU, GAMEPLAY, LOBBY, CREATELOBBY, JOINLOBBY, SETTING, CHANGEPLAYER, CHANGEENEMIES} GameScreen;
        GameScreen currentScreen;
    private:
    uint16_t _screenWidth;
    uint16_t _screenHeight;

    Vector2 _mousePoint;

    GameEngine::Background _background;
    GameEngine::Background _background2;
    GameEngine::Background _background3;
    GameEngine::Background _lobbyBackground;
    GameEngine::Background _slotBackground;
    GameEngine::Background _rtypeLogo;
    GameEngine::Background _spaceShip1;
    GameEngine::Background _spaceShip2;
    GameEngine::Background _spaceShip3;
    GameEngine::Background _spaceShip4;
    GameEngine::Background _enemy1;
    GameEngine::Background _enemy2;
    GameEngine::Background _enemy3;
    GameEngine::Background _enemy4;

    GameEngine::Text _PName;
    GameEngine::Text _P1Text;
    GameEngine::Text _TChat;
    GameEngine::Text _VolumeTitle;
    GameEngine::Text _VolumeValue;
    GameEngine::Text _Score;
    GameEngine::Text _WaveNbr;

    GameEngine::Button _joinLobbyButton;
    GameEngine::Button _playButton;
    GameEngine::Button _lobbyButton;
    GameEngine::Button _listLobbyButton;
	  GameEngine::Button _leaveButton;
    GameEngine::Button _chatBox;
    GameEngine::Button _settingButton;
    GameEngine::Button _changeSkinPlayer;
    GameEngine::Button _changeSkinEnemies;
    GameEngine::Button _rightArrow;
    GameEngine::Button _leftArrow;
    GameEngine::Button _saveButton;
    GameEngine::Button _plusButton;
    GameEngine::Button _minusButton;

    Rectangle _btnBounds;
    Rectangle _btnBounds2;
    Rectangle _btnBounds3;
	  Rectangle _btnLeaveBounds;
    Rectangle _btnSettingBounds;
    Rectangle _btnChangeSkinPlayer;
    Rectangle _btnChangeSkinEnemies;
    Rectangle _btnRightArrow;
    Rectangle _btnLeftArrow;
    Rectangle _btnSaveButton;
    Rectangle _btnPlusButton;
    Rectangle _btnMinusButton;

    int _currentSkin = 0;

    bool _isPlaying = false;

    std::string _inputText;

	std::shared_ptr<Network::Client<Network::Codes>> _client;

  SoundManager _soundManager;

  std::vector<std::string> _chatFeed;
};

#endif //R_TYPE_CLIENT_HPP