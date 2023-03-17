/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** GameLogic.hpp
*/


#ifndef GAMELOGIC_HPP_
#define GAMELOGIC_HPP_

#include <memory>
#include <random>
#include <thread>
#include <utility>
#include "Clock.hpp"
#include "Entities/Player.hpp"
#include "Entities/Enemy.hpp"
#include "Entities/Rocket.hpp"
#include "Entities/Wall.hpp"
#include "Entities/PowerUp.hpp"
#include "../../Lib/Network/include/server_it.hpp"
#include "../../Lib/Network/include/safe_queue.hpp"
#include "../../include/NetworkAlias.hpp"
#include "../../Lib/GameEngine/include/Entity/Entity.hpp"
#include "../../Lib/GameEngine/include/Components/Health.hpp"
#include "../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../Lib/GameEngine/include/Components/Hitbox.hpp"
#include "../include/thread_codes.hpp"
#include "utils/utils.hpp"

namespace Server
{
    class Lobby {
        public:
            //!  Lobby constructor
            /*!
             Pass in parameter your entityManager already created\n
             @param threadMsgOutput The pointer on the SafeQueue class
            */
            Lobby(const unsigned short int &port, std::shared_ptr<Network::SafeQueue<Network::Message<Thread::codes>>> &threadMsgOutput);
            //!  Lobby destructor
            ~Lobby();
            //! getNumberPlayers function
            /*!
             Return the number of players in the lobby
              @return The number of players in the lobby
             */
            int getNumberPlayers() const;
            //! sendMessage function
            /*!
             Send a message to the client
              @param msg The message to send
             */
			void sendMessage(const Network::Message<Thread::codes> &msg);
            //! getIdLastPlayer function
            /*!
             Return the id of the last player
              @return The id of the last player
             */
            uint32_t getIdLastPlayer();
            //! getName function
            /*!
             Return the name of the lobby
              @return The name of the lobby
             */
            std::string getName() const;
            //! getUuid function
            /*!
             Return the uuid of the lobby
              @return The uuid of the lobby
             */
            uint32_t getUuid() const;
            //! getPort function
            /*!
             Return the port of the lobby
              @return The port of the lobby
             */
			unsigned short int getPort() const;
            //! _score variable
            /*!
             The score of the lobby
             */
            uint32_t _score;
            //! getAllScores function
            /*!
                 get the scores of all the things that gave score (PowerUp class, Ennemy class etc...)
             */
            void getAllScores();
            //! sendScore function
            /*!
                 send the score to the client
             */
            void sendScore();
        private:
            //! run function
            /*!
             Run the lobby
             */
			void run();
            //! getMessages function
            /*!
             Get the messages from the client
             */
            void getMessages();
            //! addPlayer function
            /*!
             Add a player to the lobby
             @param id The id of the player
             */
			void addPlayer(const uint32_t &id);
            //! sendUpdate function
            /*!
             Send the update to the client
             */
			void sendUpdate();
            //! updatePlayerLobby function
            /*!
             Update the player in the lobby
             */
			void updatePlayerLobby();
            //! _onDisconnect function
            /*!
             The function to call when the client disconnect
             */
            std::function<void(const uint32_t &)> _onDisconnect;
            //! _name variable
            /*!
             The name of the lobby
             */
            std::string _name;
            //! _players variable
            /*!
             The players in the Game
             */
            std::unique_ptr<Server::Player> _players;
            //! _enemies variable
            /*!
             The enemies in the Game
             */
            std::unique_ptr<Server::Enemy> _enemies;
            //! _rockets variable
            /*!
             The rockets in the Game
             */
            std::unique_ptr<Server::Rocket> _rockets;
            //! _wall variable
            /*!
             The wall in the Game
             */
            std::unique_ptr<Server::Wall> _wall;
            //! _powerUp variable
            /*!
             The powerUp in the Game
             */
            std::unique_ptr<Server::PowerUp> _powerUp;
            //! _entityManager variable
            /*!
             The entityManager class for the game
             */
            std::shared_ptr<GameEngine::EntityManager> _entityManager;
            //! _server variable
            /*!
             The server class
             */
            std::shared_ptr<Network::ServerData<Network::Codes>> _server;
            //! _msgList variable
            /*!
             The list of the messages
             */
            std::shared_ptr<DataQueue> _msgList;
            //! _threadMsgOutput variable
            /*!
             The pointer on the SafeQueue class
             */
			std::shared_ptr<Network::SafeQueue<Network::Message<Thread::codes>>> _threadMsgOutput;
            //! _threadMsgInput variable
            /*!
             The pointer on the SafeQueue class
             */
			std::shared_ptr<Network::SafeQueue<Network::Message<Thread::codes>>> _threadMsgInput;
            //! _uuid variable
            /*!
             The uuid of the lobby
             */
            uint32_t _uuid;
            //! _inGame variable
            /*!
             If the game is in game (not is the lobby)
             */
			bool _inGame;
            //! _port variable
            /*!
             The port of the lobby
             */
			unsigned short int _port;
            //! _lobbyThread variable
            /*!
             The thread of the lobby
             */
			std::thread _lobbyThread;
            //! _alive variable
            /*!
             If the lobby is alive
             */
			bool _alive;
    };
} // namespace Server

#endif //GAMELOGIC_HPP_
