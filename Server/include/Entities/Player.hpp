/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Player.hpp
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "../../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../../Lib/Network//include/server_it.hpp"
#include "../../include/Entities/IEntity.hpp"
#include "../../../include/codes.hpp"

namespace Server {
    //!  Player class
    /*!
     The purpose of this class is to manage the Player (move, shoot for example)
    */
    class Player : IEntity {
    public:
        //!  Player constructor
        /*!
         Pass in parameter your entityManager already created\n
         When we shoot we have to add a new Rocket entity in the entity manager variable\n
         @param entityManager The pointer on the EntityManager class
         @param server The pointer on the Server class
        */
        Player(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server);
        ~Player();
            //!  Run function
            /*!
             Where we gonna check if the Player have to do something (move or shoot)
            */
            void run();
            //!  popPlayer function
            /*!
             Remove a Player in the _playerList variable
             @param id The id of the player to remove
            */
            void popPlayer(int id);
            //!  shoot function
            /*!
             Create a new entity Rocket in entityManager
             @param entityShooting The entity that shoot
            */
            void shoot(const std::shared_ptr<GameEngine::Entity>& entityShooting);
            //!  Move function
            /*!
             Move the player (change the position in his component Position)
             @param entity The entity that move
             @param direction The direction of the move
            */
            static void move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction);
            //!  addPlayer function
            /*!
             Add a new player in the _playerList variable
             @param newPlayer The new player to add
            */
            void addPlayer(const std::shared_ptr<GameEngine::Entity>& newPlayer);
            //! isPlayerDead function
            /*! Check if the player is dead (if his life is equal to 0)
                if the player is dead, teleport him to the death position (-1000, -1000)
                @param entity The entity to check if he is dead
            */
            bool isPlayerDead(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isPlayerTouchingEnemy function
            /*!
             Check if the player is touching an enemy
             @param entity The entity to check if he is touching an enemy
            */
            void isPlayerTouchingEnemy(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isPositionValid function
            /*!
             Check if the position is valid (if the player is not going out of the map)
             @param entity The entity to check if his position is valid
            */
            bool isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity);
            //! findNumberPlayer function
            /*!
             Return the number of player alive
            */
            int findNumberPlayer();
            //! loseCondition function
            /*!
             Check if the game is over
            @return true if the game is over, false if not
            */
            bool loseCondition();
            //!  _playerList variable
            /*!
             The list of all the players alive (it's a shared pointer on the class Entity)
            */
            std::vector<std::shared_ptr<GameEngine::Entity>> _playerList;
            //!  _actionQueue variable
            /*!
             The list of all messages for all players
            */
            std::vector<std::vector<GameEngine::Actions>> _actionQueue;
            //! checkPartylunsh function
            /*!
             Check if the party is ready to start
            */
            void checkPartylunsh(void);
            //!  sendUpdateMessage function
            /*!
             Send the update message to the client
             @param entity The entity to send
            */
            void sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isInGame variable
            /*!
             Check if the game is started
            */
            bool isInGame = false;
    private:
        //!  _entityManager variable
        /*!
         The pointer on the EntityManager class
        */
        std::shared_ptr<GameEngine::EntityManager> _entityManager;
        //! _server variable
        /*!
         The pointer on the server
        */
        std::shared_ptr<Network::ServerData<Network::Codes>> _server;
        //!  _onDisconnect variable
        /*!
         The function to call when a player disconnect
        */
        std::function<void(const uint32_t &)> _onDisconnect;

    };
}
#endif /* !PLAYER_HPP_ */