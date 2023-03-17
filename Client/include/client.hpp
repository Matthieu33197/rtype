/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** client.hpp
*/

#ifndef R_TYPE_CLIENT_HPP
	#define R_TYPE_CLIENT_HPP

	#include <iostream>
	#include <raylib.h>
	#include <unordered_map>
	#include <tuple>
	#include "../../Lib/GameEngine/include/Utils/Background.hpp"
	#include "../../Lib/GameEngine/include/Utils/Button.hpp"
	#include "../../Lib/GameEngine/include/Components/Style.hpp"
	#include "screen.hpp"
	#include "entityHandler.hpp"
	#include "../../include/NetworkAlias.hpp"

namespace Game {
	class Client {
		public:
			//! Client constructor
			/*!
		 	 The constructor will initialize the client
	   		*/
			Client(const std::string &host, const unsigned short int &port);
			//! Client destructor
			/*!
		 	 The destructor will unload the client
	   		*/
			~Client();
			//! start function
        	/*!
         	 The function will make the necessary calls to intialize the game client
       		*/
			int start();
			//! run function
        	/*!
         	 Main gale loop where the incomming messages are checked and the screens are handled
       		*/
			void run();
			//! sendPlayerShoot function
        	/*!
         	 The function sends a message to the server that the player is shooting
       		*/
			void sendPlayerShoot();
			//! getInput function
        	/*!
         	 The function gets the incoming messages from the server
       		*/
			void getInput();
			//! display function
        	/*!
         	 The function manages the diffrent display states of the game (also calles screens)
       		*/
			void display();
			//! checkMessages function
        	/*!
         	 The function reroutes the incoming messages to the right function
       		*/
			void checkMessages();
			//! connectData function
        	/*!
         	 The function passes the right parameter to start the mukltiplayer experience (UDP connection)
       		*/
			int connectData(CombOwnedMsg &msg);
			//! setID function
			/*!
		 	 The function sets the id of the player
	   		*/
			int setID(CombOwnedMsg &msg);
			//! setScore function
			/*!
		 	 The function sets the score of the player
	   		*/
			int updateScore(CombOwnedMsg &msg);
			//! saveLobbyList function
        	/*!
         	 The function gets all the lobbies from the server
       		*/
			int updateWaveNumber(CombOwnedMsg &msg);
			int saveLobbyList(CombOwnedMsg &msg);
			//! savePlayerList function
        	/*!
         	 The function gets all the players from the server
       		*/
			int savePlayerList(CombOwnedMsg &owner);
			//! saveTChat function
        	/*!
         	 The function gets all the chat messages from the server
       		*/
			int saveTChat(CombOwnedMsg &owner);
			//! id variable
			/*!
		 	 The variable is the id of the player
	   		*/
			uint32_t id;
			//! _score variable
			/*!
		 	 The variable is the score of the player
	   		*/
			uint32_t _score;
			uint32_t _waveNbr;
		private:
			bool _preLoaded;
			EntityHandler _entityHandler;
			std::shared_ptr<CombQueue> _msgList;
			Screen _screen;
			Network::Message<Network::Codes> _msg;
			std::unordered_map<Network::Codes, std::function<int(CombOwnedMsg &)>> _cmds;
			std::shared_ptr<Network::Client<Network::Codes>> _client;
			std::vector<std::tuple<int, uint32_t>> _lobbyList;
			std::vector<uint32_t> _playerIDList;

			std::string _TChat;
			std::string _TChatTMP;
			std::vector<std::string> _TChatList;
	};
}

#endif //R_TYPE_CLIENT_HPP
