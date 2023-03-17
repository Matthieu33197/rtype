/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enemy.hpp
*/

#ifndef ENEMY_HPP_
#define ENEMY_HPP_

#include "../../../Lib/GameEngine/include/Entity/EntityManager.hpp"
#include "../../../Lib/Network/include/server_it.hpp"
#include "../../../include/codes.hpp"
#include "IEntity.hpp"

namespace Server {
    //!  Enemy class
    /*!
      The purpose of this class is to manage the Enemy (move, shoot for example)
    */
    class Enemy : IEntity {
    public:
        //!  Enemy constructor
        /*!
         Pass in parameter your entityManager already created\n
         When we shoot a new Rocket entity is added in the EntityManger variable (_entityManager)\n
         @param entityManager The pointer on the EntityManager class
         @param server The pointer on the Server class
        */
        Enemy(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server);        //! Enemy destructor
        /*!
         Delete the Enemy
        */
        ~Enemy() = default;
        //!  run function
        /*!
         Where we gonna check if the Enemy have to do something (move or shoot)
        */
        void run();
        //!  shoot function
        /*!
         Make the enemy shoot
         @param entityShooting The entity that is shooting
        */

        bool winCondition();
        //! randPowerUpEnemy function
        /*!
         Generate a random powerUp for the enemy
         @param entity The entity that is shooting
        */
        void randPowerUpEnemy(const std::shared_ptr<GameEngine::Entity>& entity);
        //!  enemyShoot function
        /*!
         Make the enemy shoot
         @param entity The entity that is shooting
        */
        void enemyShoot(const std::shared_ptr<GameEngine::Entity>& entity);

        void shoot(const std::shared_ptr<GameEngine::Entity>& entityShooting);
        //!  move function
        /*!
         Move the enemy (change the position in his Position component)
         @param entity The entity that is moving
         @param direction The direction of the movement
        */
        void move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction);
        //!  generateWave function
        /*!
         Generate a new wave of enemy
        */
        bool isGameRunnable();
        //!  addPowerUp function
        /*!
         Add a powerUp in the _powerUpList variable
         @param entity The entity that is moving
        */
        void addPowerUp(const std::shared_ptr<GameEngine::Entity>& entity);

        void generateWave(void);
        //!  generateBoss function
        /*!
         Generate a new boss
        */
        void generateBoss(void);
        //!  findNumberPlayer function
        /*!
         Find the number of player in the _playerList variable
        */
        int findNumberPlayer(void);

        //!  findNumberEnemy function
        /*!
         Find the number of enemy in the _enemyList variable
        */
        int findNumberEnemy(void);
        //!  isEnemyPositionValid function
        /*!
         Check if the position of the enemy is valid (if he is not out of the screen)
         @param entity The entity that is moving
        */
        void isEnemyPositionValid(const std::shared_ptr<GameEngine::Entity>& entity);
        //!  changeDirrection function
        /*!
         Change the direction of the enemy
         @param entity The entity that is moving
        */
        void changeDirrection(const std::shared_ptr<GameEngine::Entity>& entity);
        //!  getDifficulty function
        /*!
         Get the difficulty of the game
         @return The difficulty of the game
        */
        int getDifficulty(void) const;
        //!  setDifficulty function
        /*!
         Set the difficulty of the game
         @param difficulty The difficulty of the game
        */
        void setDifficulty(int difficulty);
        //!  getWave function
        /*!
         Get the wave of the game
         @return The wave of the game
        */
        int getWave(void) const;
        //!  setWave function
        /*!
         Set the wave of the game
         @param wave The wave of the game
        */
        void setWave(int wave);
        //! sendUpdataMessage function
        /*!
         Send the update message to all the clients
        */
        void sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity);
        //!  getIsInGame function
        /*!
         Get the isInGame of the game
         @return The isInGame of the game
        */
        bool getIsInGame(void) const;
        //! setIsInGame function
        /*!
            modifie the isInGame variable
            true = the game is lunsh
            false = the game is stop.
        */
        void setIsInGame(bool isInGame);
        //! setRandDirrection function
        /*!
            set a random direction to the enemy
            @param entity the enemy
        */
        void setRandDirrection(const std::shared_ptr<GameEngine::Entity>& entity);
        //!  getIsWaveBoss function
        /*!
         Get the isWaveBoss of the game
         @return The isWaveBoss of the game
        */
        uint32_t _score;
        //!  getScore function
        /*!
         Get the score of the game
         @return The score of the game
        */
        int directionCooldown = 1000;
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
        //! _difficulty variable
        /*!
         The difficulty of the game
        */
        int _difficulty;
        //! _wave variable
        /*!
         The wave of the game
        */
        int _wave;
        //! isInGame variable
        /*!
         The game is running or not
        */
        bool isInGame;
        //! _isWaveBoss variable
        /*!
         The wave is a boss or not
        */
        bool _isWaveBoss;
    };
}

#endif /* !ENEMY_HPP_ */