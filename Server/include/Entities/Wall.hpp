/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rocket.hpp
*/

#ifndef WALL_HPP_
#define WALL_HPP_

#include "../../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../../Lib/Network//include/server_it.hpp"
#include "../../include/Entities/IEntity.hpp"
#include "../../../include/codes.hpp"

namespace Server {
    //!  Rocket class
    /*!
     The purpose of this class is to manage the Rocket (move, shoot for example)
    */
    class Wall : IEntity {
        public:
            //!  Rocket constructor
            /*!
             Pass in parameter your entityManager already created\n
             When we shoot we have to add a new Rocket entity in the entity manager variable\n
             @param entityManager The pointer on the EntityManager class
             @param server The pointer on the Server class
            */
            Wall(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server);
            ~Wall();
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
            void move(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  isPositionValid function
            /*!
             Check if the position of the Rocket is valid (if it's not in the map)
             @param entity The entity that we check
            */
            bool isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity);
            //! hitByRocket function
            /*!
             Check if a Rocket hit a wall
             @param entity The entity that we check
            */
            bool hitByRocket(const std::shared_ptr<GameEngine::Entity>& entity, const std::shared_ptr<GameEngine::Entity>& rocket);
            //!  hittingPlayer function
            /*!
             Check if the Wall is hitting a player
             @param entity The entity that we check
            */
            void hittingPlayer(const std::shared_ptr<GameEngine::Entity>& entity, const std::shared_ptr<GameEngine::Entity>& player);
            //! generateWall function
            /*!
             Generate a wall
            */
            void generateWall();
            //! destroyWall function
            /*!
             Destroy a wall
             @param entity The entity that we destroy
            */
            void destroyWall(const std::shared_ptr<GameEngine::Entity>& entity);
            //! destroyEntity function
            /*!
             Destroy an entity
             @param entity The entity that we destroy
            */
            void destroyEntity(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  checkColisionPlayer function
            /*!
             Check if the Wall is in collision with a player
             @param entity The entity that we check
             @param player The player that we check
            */
            void checkColisionPlayer(const std::shared_ptr<GameEngine::Entity>& entity, const std::shared_ptr<GameEngine::Entity>& player);
            //!  checkColisionRocket function
            /*!
             Check if the Wall is in collision with a Rocket
             @param entity The entity that we check
             @param rocket The Rocket that we check
            */
            void checkColisionRocket(const std::shared_ptr<GameEngine::Entity>& entity, const std::shared_ptr<GameEngine::Entity>& rocket);
            //!  checkColision function
            /*!
             Check if the Wall is in collision with something
             @param entity The entity that we check
            */
            void checkColision(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  addPowerUp function
            /*!
             Add a power up
             @param entity The entity that we add
            */
            void addPowerUp(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  canGenerateWall function
            /*!
             Check if we can generate a wall
            */
            void canGenerateWall(void);
            //!  sendUpdateMessage function
            /*!
             Send the update of the Wall to the client
             @param entity The entity that we send
            */
            void sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity);
            int cooldown2 = 1000;
            uint32_t _score;
        private:
        //!  _entityManager variable
        /*!
         The pointer on the EntityManager class
        */
        std::shared_ptr<GameEngine::EntityManager> _entityManager;
        //! _server variable
        /*!
         The pointer on the server
         It is useful to send the update of the Enemies to the client (position, if an Enemy is dead to unload it, etc...)
        */
        std::shared_ptr<Network::ServerData<Network::Codes>> _server;
    };
}
#endif /* !WALL_HPP_ */