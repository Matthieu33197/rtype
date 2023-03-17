/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** EntityManager.cpp
*/

#include <string>
#include "../include/Components/Health.hpp"
#include "../include/Components/Cooldown.hpp"
#include "../include/Entity/EntityManager.hpp"
#include "../include/Components/Damages.hpp"
#include "../include/Components/Position.hpp"
#include "../include/Components/Hitbox.hpp"
#include "../include/Components/Style.hpp"
#include "../include/Components/Friendly.hpp"
#include "../include/Components/Speed.hpp"

GameEngine::EntityManager::EntityManager()
{
    _id = 0;
}

GameEngine::EntityManager::~EntityManager()
{

}

void GameEngine::EntityManager::popEntity(int id)
{
    for (int i = 0; i < _entityList.size(); i++) {
        if (_entityList[i]->_id == id)
            _entityList.erase(_entityList.begin() + i);
    }
}

std::shared_ptr<GameEngine::Entity> GameEngine::EntityManager::CreatePlayer(uint16_t health, uint16_t damages, uint16_t speed, const std::string &path,
                                                                            Vector2 position, int cooldown)
{
    std::shared_ptr<Entity> playerEntity = std::make_shared<Entity>(_id);
    Rectangle hitbox = {0.0f, 0.0f, 0.0f, 0.0f};

    std::shared_ptr<GameEngine::Style> styleComponent =
            std::make_shared<GameEngine::Style>(path);
    std::shared_ptr<GameEngine::Health> healthComponent =
            std::make_shared<GameEngine::Health>(health);
    std::shared_ptr<GameEngine::Damages> damagesComponent =
            std::make_shared<GameEngine::Damages>(damages);
    std::shared_ptr<GameEngine::Position> posComponent =
            std::make_shared<GameEngine::Position>(position.x, position.y);
    std::shared_ptr<GameEngine::Hitbox> hitboxComponent =
            std::make_shared<GameEngine::Hitbox>(hitbox);
    std::shared_ptr<GameEngine::Speed> speedComponent =
            std::make_shared<GameEngine::Speed>(speed);
    std::shared_ptr<GameEngine::Cooldown> cooldownComponent =
            std::make_shared<GameEngine::Cooldown>(cooldown);

    playerEntity->addComp<GameEngine::Health>(healthComponent);
    playerEntity->addComp<GameEngine::Cooldown>(cooldownComponent);
    playerEntity->addComp<GameEngine::Damages>(damagesComponent);
    playerEntity->addComp<GameEngine::Position>(posComponent);
    playerEntity->addComp<GameEngine::Hitbox>(hitboxComponent);
    playerEntity->addComp<GameEngine::Style>(styleComponent);
    playerEntity->addComp<GameEngine::Speed>(speedComponent);
    playerEntity->_type = GameEngine::EntityType::PLAYER;

    _entityList.push_back(playerEntity);
    _id += 1;
    return (playerEntity);
}

std::shared_ptr<GameEngine::Entity> GameEngine::EntityManager::CreatePowerUp(uint16_t speed, const std::string &path,
                                                                            Vector2 position)
{
    std::shared_ptr<Entity> powerUpEntity = std::make_shared<Entity>(_id);
    Rectangle hitbox = {0.0f, 0.0f, 0.0f, 0.0f};

    std::shared_ptr<GameEngine::Style> styleComponent =
            std::make_shared<GameEngine::Style>(path);
    std::shared_ptr<GameEngine::Position> posComponent =
            std::make_shared<GameEngine::Position>(position.x, position.y);
    std::shared_ptr<GameEngine::Hitbox> hitboxComponent =
            std::make_shared<GameEngine::Hitbox>(hitbox);
    std::shared_ptr<GameEngine::Speed> speedComponent =
            std::make_shared<GameEngine::Speed>(speed);

    powerUpEntity->addComp<GameEngine::Position>(posComponent);
    powerUpEntity->addComp<GameEngine::Hitbox>(hitboxComponent);
    powerUpEntity->addComp<GameEngine::Style>(styleComponent);
    powerUpEntity->addComp<GameEngine::Speed>(speedComponent);
    powerUpEntity->_type = GameEngine::EntityType::POWERUP;

    _entityList.push_back(powerUpEntity);
    _id += 1;
    return (powerUpEntity);
}

std::shared_ptr<GameEngine::Entity> GameEngine::EntityManager::CreateEnemy(
        uint16_t health, uint16_t damages, int cooldown, uint16_t speed, const std::string &path, Vector2 position)
{
    std::shared_ptr<Entity> enemyEntity = std::make_shared<Entity>
            (_id);
    Rectangle hitbox = {0.0f, 0.0f, 0.0f, 0.0f};
        
    std::shared_ptr<GameEngine::Style> styleComponent =
            std::make_shared<GameEngine::Style>(path);
    std::shared_ptr<GameEngine::Health> healthComponent =
            std::make_shared<GameEngine::Health>(health);
    std::shared_ptr<GameEngine::Damages> damagesComponent =
            std::make_shared<GameEngine::Damages>(damages);
    std::shared_ptr<GameEngine::Position> posComponent =
            std::make_shared<GameEngine::Position>(position.x, position.y);
    std::shared_ptr<GameEngine::Hitbox> hitboxComponent =
            std::make_shared<GameEngine::Hitbox>(hitbox);
    std::shared_ptr<GameEngine::Speed> speedComponent =
            std::make_shared<GameEngine::Speed>(speed);
    std::shared_ptr<GameEngine::Cooldown> cooldownComponent =
            std::make_shared<GameEngine::Cooldown>(cooldown);

    enemyEntity->addComp<GameEngine::Cooldown>(cooldownComponent);
    enemyEntity->addComp<GameEngine::Health>(healthComponent);
    enemyEntity->addComp<GameEngine::Damages>(damagesComponent);
    enemyEntity->addComp<GameEngine::Position>(posComponent);
    enemyEntity->addComp<GameEngine::Hitbox>(hitboxComponent);
    enemyEntity->addComp<GameEngine::Style>(styleComponent);
    enemyEntity->addComp<GameEngine::Speed>(speedComponent);
    enemyEntity->_type = GameEngine::ENEMY;

    _entityList.push_back(enemyEntity);
    _id += 1;

    return (enemyEntity);
}

std::shared_ptr<GameEngine::Entity> GameEngine::EntityManager::CreateRocket(
        uint16_t damages, uint16_t speed, const std::string &path, Vector2 position, bool friendly)
{
    std::shared_ptr<Entity> rocketEntity = std::make_shared<Entity>(_id);
    Rectangle hitbox = {0.0f, 0.0f, 0.0f, 0.0f};

    std::shared_ptr<GameEngine::Style> styleComponent =
            std::make_shared<GameEngine::Style>(path);
    std::shared_ptr<GameEngine::Damages> damagesComponent =
            std::make_shared<GameEngine::Damages>(damages);
    std::shared_ptr<GameEngine::Position> posComponent =
            std::make_shared<GameEngine::Position>(position.x, position.y);
    std::shared_ptr<GameEngine::Hitbox> hitboxComponent =
            std::make_shared<GameEngine::Hitbox>(hitbox);
    std::shared_ptr<GameEngine::Speed> speedComponent =
            std::make_shared<GameEngine::Speed>(speed);
    std::shared_ptr<GameEngine::Friendly> friendlyComponent =
            std::make_shared<GameEngine::Friendly>(friendly);


    rocketEntity->addComp<GameEngine::Damages>(damagesComponent);
    rocketEntity->addComp<GameEngine::Position>(posComponent);
    rocketEntity->addComp<GameEngine::Hitbox>(hitboxComponent);
    rocketEntity->addComp<GameEngine::Style>(styleComponent);
    rocketEntity->addComp<GameEngine::Speed>(speedComponent);
    rocketEntity->addComp<GameEngine::Friendly>(friendlyComponent);
    rocketEntity->_type = GameEngine::EntityType::ROCKET;

    _entityList.push_back(rocketEntity);
    _id += 1;

    return (rocketEntity);
}

std::shared_ptr<GameEngine::Entity> GameEngine::EntityManager::CreateWall(uint16_t health, uint16_t damages, uint16_t speed, const std::string &path,
                                                                            Vector2 position)
{
    std::shared_ptr<Entity> wallEntity = std::make_shared<Entity>(_id);
    Rectangle hitbox = {0.0f, 0.0f, 0.0f, 0.0f};

    std::shared_ptr<GameEngine::Style> styleComponent =
            std::make_shared<GameEngine::Style>(path);
    std::shared_ptr<GameEngine::Health> healthComponent =
            std::make_shared<GameEngine::Health>(health);
    std::shared_ptr<GameEngine::Damages> damagesComponent =
            std::make_shared<GameEngine::Damages>(damages);
    std::shared_ptr<GameEngine::Position> posComponent =
            std::make_shared<GameEngine::Position>(position.x, position.y);
    std::shared_ptr<GameEngine::Hitbox> hitboxComponent =
            std::make_shared<GameEngine::Hitbox>(hitbox);
    std::shared_ptr<GameEngine::Speed> speedComponent =
            std::make_shared<GameEngine::Speed>(speed);

    wallEntity->addComp<GameEngine::Health>(healthComponent);
    wallEntity->addComp<GameEngine::Damages>(damagesComponent);
    wallEntity->addComp<GameEngine::Position>(posComponent);
    wallEntity->addComp<GameEngine::Hitbox>(hitboxComponent);
    wallEntity->addComp<GameEngine::Style>(styleComponent);
    wallEntity->addComp<GameEngine::Speed>(speedComponent);
    wallEntity->_type = GameEngine::WALL;

    _entityList.push_back(wallEntity);
    _id += 1;
    return (wallEntity);
}

std::vector<std::shared_ptr<GameEngine::Entity>> GameEngine::EntityManager::getEntityList()
{
    return (_entityList);
}