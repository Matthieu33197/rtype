/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rocket.hpp
*/

#ifndef ROCKET_HPP_
#define ROCKET_HPP_

#include "../../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../../Lib/Network//include/server_it.hpp"
#include "../../include/Entities/IEntity.hpp"
#include "../../../include/codes.hpp"

namespace Server {
    //!  Rocket class
    /*!
     The purpose of this class is to manage the Rocket (move, shoot for example)
    */
    class Rocket : IEntity {
    public:
        //!  Rocket constructor
        /*!
         Pass in parameter your entityManager already created\n
         When we shoot we have to add a new Rocket entity in the entity manager variable\n
         @param entityManager The pointer on the EntityManager class
         @param server The pointer on the Server class
        */
        Rocket(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server);
        //!  Rocket destructor
        /*!
         Delete the Rocket
        */
        ~Rocket();
            //!  Run function
            /*!
             Where we gonna check if the Rocket have to do something (move or shoot), or if the Rocket is in collision with something (player, wall, etc...)
            */
            void run();
            //!  Move function
            /*!
             Move the Rocket (change the position in his component Position)
             @param entity The entity that move
             @param direction The direction of the move
            */
            void move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction);
            //!  isPositionValid function
            /*!
             Check if the position of the Rocket is valid (if it's not in the map)
             @param entity The entity that we check
            */
            bool isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isHitPlayer function
            /*!
             Check if the Rocket is hitting a player
             @param entity The entity that we check
            */
            void isHittingPlayer(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isHitEnemy function
            /*!
             Check if the Rocket is hitting an enemy
             @param entity The entity that we check
            */
            void isHittingEnemy(const std::shared_ptr<GameEngine::Entity>& entity);
            //! sendUpdateMessage function
            /*!
             Send the update message to the client
             @param entity The entity that we send
            */
            void sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity);

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

    };
}
#endif /* !Rocket_HPP_ */