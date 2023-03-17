/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PowerUp.hpp
*/

#ifndef POWERUP_HPP_
#define POWERUP_HPP_

#include "../../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../../Lib/Network//include/server_it.hpp"
#include "../../include/Entities/IEntity.hpp"
#include "../../../include/codes.hpp"

namespace Server {
    //!  Player class
    /*!
     The purpose of this class is to manage the PowerUp
    */
    class PowerUp : IEntity {
    public:
        //!  PowerUp constructor
        /*!
         Pass in parameter your entityManager already created\n
         @param entityManager The pointer on the EntityManager class
        */
        PowerUp(std::shared_ptr<GameEngine::EntityManager> &entityManager , std::shared_ptr<Network::ServerData<Network::Codes>> &server);
        ~PowerUp();
            //!  Run function
            /*!
             Where we gonna check if the Player have to do something (move or shoot)
            */
            void run();
            //! applyPowerUp function
            /*!
              Apply a powerUp
              @param powerUp The powerUp to apply
              @param rand The random number to know which powerUp to apply
            */
            void applyPowerUp(const std::shared_ptr<GameEngine::Entity>& powerUp, int rand);
            //! popPowerUp function
            /*!
              Remove a PowerUp in the _powerUpList variable
              @param powerUp The powerUp to remove
            */
            void popPowerUp(const std::shared_ptr<GameEngine::Entity>& powerUp);
            //! countPowerUp function
            /*!
              Count the number of powerUp in the _powerUpList variable
            */
            int countPowerUp();
            //! dropPowerUp function
            /*!
              Drop a powerUp
              @param entity The entity that drop the powerUp
            */
            bool playerDropPowerUp(const std::shared_ptr<GameEngine::Entity>& powerUp);
            //! move function
            /*!
             Move the powerUp (change the position in his component Position)
             @param entity The entity that move
             @param direction The direction of the move
            */
            void move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction);
            //!  isPositionValid function
            /*!
             Check if the position of the PowerUp is valid (if it's not in the map)
             @param entity The entity that we want to check
            */
            bool isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity);
            //! restoreHealth function
            /*!
             Restore the health of the player
             @param entity The entity that we want to restore the health
            */
            void restoreHealth(const std::shared_ptr<GameEngine::Entity>& entity);
            //! restoreTeamHealth function
            /*!
             Restore the health of every player in the team
             @param entity The entity that we want to restore the health
            */
            void restoreTeamHealth(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffDamages function
            /*!
             Buff the damages of the player
             @param entity The entity that we want to buff the damages
            */
            void buffDamages(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffTeamDamages function
            /*!
             Buff the damages of every player in the team
             @param entity The entity that we want to buff the damages
            */
            void buffTeamDamages(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffSpeed function
            /*!
             Buff the speed of the player
             @param entity The entity that we want to buff the speed
            */
            void buffSpeed(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffTeamSpeed function
            /*!
             Buff the speed of every player in the team
             @param entity The entity that we want to buff the speed
            */
            void buffTeamSpeed(const std::shared_ptr<GameEngine::Entity>& entity);
            //! sendUpdateMessage function
            /*!
             Send the update message to the client
             @param entity The entity that we want to send the update message
            */
            void sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffFireRate function
            /*!
             Buff the fireRate of the player
             @param entity The entity that we want to buff the fireRate
            */
            void buffFireRate(const std::shared_ptr<GameEngine::Entity>& entity);
            //! buffTeamFireRate function
            /*!
             Buff the fireRate of every player in the team
             @param entity The entity that we want to buff the fireRate
            */
            void buffTeamFireRate(const std::shared_ptr<GameEngine::Entity>& entity);
            //!  _actionQueue variable
            /*!
             The list of all messages for all players
            */
            std::vector<std::vector<GameEngine::Actions>> _actionQueue;
            //!  _powerUpList variable
            /*!
              the list of all powerUp
            */
            std::vector<std::shared_ptr<GameEngine::Entity>> _powerUpList;
            //! _score variable
            //! The score of the player
            uint32_t _score;
    private:
        //!  _entityManager variable
        /*!
         The pointer on the EntityManager class
        */
        std::shared_ptr<GameEngine::EntityManager> _entityManager;
        //!  _server variable
        /*!
         The pointer on the ServerData class
        */
        std::shared_ptr<Network::ServerData<Network::Codes>> _server;
    };
}
#endif /* !POWERUP_HPP_ */