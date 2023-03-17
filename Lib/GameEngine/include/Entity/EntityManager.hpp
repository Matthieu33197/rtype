/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityManager.hpp
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "raylib.h"
#include <vector>
#include <memory>
#include <chrono>
#include "Entity.hpp"

namespace GameEngine {
    //!  EntityManager class
    /*!
      The purpose of this class is to have the list of all entities created in the game.\n
      The goal is also to be able to create new entities and store them in the same variable: _entityList.\n
      Here we can create a Player Entity, an Enemy Entity, a Rocket Entity.\n
    */
    class EntityManager {
    public:
        EntityManager();
        ~EntityManager();
        //! CreatePlayer function
        /*!
         Create a Player entity\n
         You need to pass several informations on the components of this entity (health, Damages, Speed, Texture, Position)\n
         @param health the health of the player
         @param damages the damages of the player
         @param speed the speed of the player
         @param path the path of the texture of the player
         @param position the position of the player
         */
        std::shared_ptr<GameEngine::Entity> CreatePlayer(uint16_t health = CONST_HEALTH, uint16_t damages = CONST_DAMAGES, uint16_t speed = CONST_SPEED, const std::string &path = "NULL", Vector2 position = {0, 0}, int cooldown = CONST_COOLDOWN);
        //! CreateEnemy function
        /*!
         Create an Enemy entity\n
         You need to pass several informations on the components of this entity (health, Damages, Speed, Texture, Position, Cooldown)\n
         @param health the health of the player
         @param damages the damages of the player
         @param speed the speed of the player
         @param path the path of the texture of the player
         @param position the position of the player
         @param cooldown the cooldown for the shoot of the player
         */
        std::shared_ptr<GameEngine::Entity> CreateEnemy(uint16_t health = CONST_HEALTH, uint16_t damages = CONST_DAMAGES, int cooldown = CONST_COOLDOWN, uint16_t speed = CONST_SPEED, const std::string &path = "NULL", Vector2 position = {0, 0});
        //! CreateRocket function
        /*!
         Create a Rocket entity\n
         You need to pass several informations on the components of this entity (Damages, Speed, Cooldown, Texture, Position)\n
         @param damages the damages of the player
         @param speed the speed of the player
         @param cooldown the cooldown of the shoot of the player
         @param path the path of the texture of the player
         @param position the position of the player
         @param friendly the position of the player
         */
        std::shared_ptr<GameEngine::Entity> CreateRocket(uint16_t damages = CONST_DAMAGES, uint16_t speed = CONST_SPEED, const std::string &path = "NULL", Vector2 position = {0, 0}, bool friendly = false);
        //! CreatePowerUp function
        /*!
         Create a PowerUp entity\n
         You need to pass several informations on the components of this entity (health, Damages, Speed, Texture, Position)\n
         @param health the health of the player
         @param damages the damages of the player
         @param speed the speed of the player
         @param path the path of the texture of the player
         @param position the position of the player
         */
        std::shared_ptr<GameEngine::Entity> CreatePowerUp(uint16_t speed = CONST_SPEED, const std::string &path = "NULL", Vector2 position = {0, 0});
        //! CreateWall function
        /*!
         Create a Wall entity\n
         You need to pass several informations on the components of this entity (health, Damages, Speed, Texture, Position)\n
         @param health the health of the player
         @param damages the damages of the player
         @param speed the speed of the player
         @param path the path of the texture of the player
         @param position the position of the player
         */
        std::shared_ptr<GameEngine::Entity> CreateWall(uint16_t health = CONST_HEALTH, uint16_t damages = CONST_DAMAGES, uint16_t speed = CONST_SPEED, const std::string &path = "NULL", Vector2 position = {0, 0});
        //! popEntity function
        /*!
         Pop an Entity in the _entityList\n
         Find an entity by ID and then remove it.\n
         It can be usefull when an entity die, you can remove it quickly\n
         @param id the id of the entity you want to removep
         */
        void popEntity(int id);
        //! getEntityList function
        /*!
         get the variable _entityList\n
         @param no parameters needed
         @return the variable _entityList
         */
        std::vector<std::shared_ptr<GameEngine::Entity>> getEntityList();
    private:
        //! _entityList variable
        /*!
         The list of all entities alive in the game.
         It can be players, monsters or rockets.
         */
        std::vector<std::shared_ptr<GameEngine::Entity>> _entityList;
        //! _id variable
        /*!
         The maximum ID
         It increase each times a new entity is created
         */
        uint32_t _id;
    };
}

#endif /* ENTITYMANAGER_HPP_ */