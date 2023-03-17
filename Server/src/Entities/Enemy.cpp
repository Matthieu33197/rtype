/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Enemy.cpp
*/

#include "../../include/Entities/Enemy.hpp"
#include "../../include/Lobby.hpp"
#include "../../../Lib/GameEngine/include/Components/Speed.hpp"
#include "../../../Lib/GameEngine/include/Components/Damages.hpp"
#include "../../../Lib/GameEngine/include/Components/Cooldown.hpp"
#include "../../include/utils/unloadId.hpp"
#include "../../include/utils/sendWaveNumber.hpp"

#define RAND_POWERUP 10

Server::Enemy::Enemy(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server)
: _entityManager(entityManager), _server(server)
{
    setDifficulty(1);
    setWave(0);
    setIsInGame(false);
    _score = 0;
    _isWaveBoss = false;
}

void Server::Enemy::run()
{
    if (winCondition() == true) {
        std::cout << "You win" << std::endl;
    }
    for(int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (getIsInGame() == false)
            isGameRunnable();
        if (getIsInGame() == true) {
            if (findNumberEnemy() == 0) {
                if (getWave() % 5 == 0 && getWave() != 0) {
                    _isWaveBoss = true;
                    generateBoss();
                    setDifficulty(getDifficulty() + (findNumberPlayer()));
                    setWave(getWave() + 1);
                    sendWaveNumber((uint32_t)getWave(), _server);
                } else {
                    _isWaveBoss = false;
                    generateWave();
                    setWave(getWave() + 1);
                    sendWaveNumber(getWave(), _server);
                }
                break;
            }

            if (_entityManager->getEntityList()[i]->_type == GameEngine::ENEMY) {
                auto ptr = _entityManager->getEntityList()[i];
                if (ptr->getComp<GameEngine::Health>()->_health <= 0) {
                    sendMessageUnloadID(_entityManager->getEntityList()[i]->_id, _server);
                    randPowerUpEnemy(ptr);
                    _entityManager->popEntity(_entityManager->getEntityList()[i]->_id);
                    if (_isWaveBoss == true) {
                        _score += 100;
                    } else {
                        _score += 10;
                    }
                    continue;
                }
                isEnemyPositionValid(ptr);
                move(ptr, ptr->getComp<GameEngine::Position>()->_direction);
                enemyShoot(ptr);
            }
        }
    }
}

bool Server::Enemy::isGameRunnable()
{
    if (findNumberPlayer() < MINIMUM_PLAYER) {
        return false;
    }
    setIsInGame(true);
    return true;
}

void Server::Enemy::enemyShoot(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    if (entity->getComp<GameEngine::Cooldown>()->isCooldownFinish())
        shoot(entity);
}

void Server::Enemy::addPowerUp(const std::shared_ptr<GameEngine::Entity>& entity) {
    _entityManager->CreatePowerUp(
        GameEngine::CONST_SPEED / 10,
        "", 
        entity->getComp<GameEngine::Position>()->getPosition()
    );

    _entityManager->getEntityList().back()->getComp<GameEngine::Hitbox>()->_hitbox = {50, 50, 50, 50};
    _entityManager->getEntityList().back()->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_LEFT;
    _entityManager->getEntityList().back()->getComp<GameEngine::Speed>()->_speed = 1;
}

bool Server::Enemy::winCondition()
{
    if (getWave() + 1 == 20) {
        return true;
    }
    return false;
}


void Server::Enemy::randPowerUpEnemy(const std::shared_ptr<GameEngine::Entity>& entity)
{
    auto entityShooting = entity;

    int rand = std::rand() % 100 + 1;
    if (rand <= RAND_POWERUP) {
        _entityManager->CreatePowerUp(static_cast<uint16_t>(0), "", entityShooting->getComp<GameEngine::Position>()->getPosition());

    }
}

int Server::Enemy::findNumberPlayer()
{
    int count = 0;

    for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::PLAYER) {
            count++;
        }
    }
    return (count);
}

void Server::Enemy::setRandDirrection(const std::shared_ptr<GameEngine::Entity>& entity)
{
    int rand = std::rand() % 4;

    if (rand == 0) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_UP;
    } else if (rand == 1) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_DOWN;
    } else if (rand == 2) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_LEFT;
    } else if (rand == 3) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_RIGHT;
    }
}

void Server::Enemy::sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::UPDATE_ENTITIES;
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().y);
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().x);
    messageUpdate << static_cast<uint8_t>(entity->_type);
    messageUpdate << static_cast<uint32_t>(entity->_id);
    _server->notifiyClients(messageUpdate);
}

int Server::Enemy::findNumberEnemy()
{
    int count = 0;

    for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::ENEMY) {
            count++;
        }
    }
    return (count);
}

void Server::Enemy::generateWave(void) {
    int i = (int) sqrt(getDifficulty()) + (rand() % findNumberPlayer());
    while (i > 0) {
        _entityManager->CreateEnemy(
            GameEngine::CONST_HEALTH * i * 3,
            GameEngine::CONST_DAMAGES,
            GameEngine::CONST_COOLDOWN + 700 - (rand() % (i * 10)),
            GameEngine::CONST_SPEED / 15, 
            "", 
            {(float)(rand() % 1000 + 980), (float)(rand() % 1080)}
        );
        _entityManager->getEntityList().back()->getComp<GameEngine::Hitbox>()->_hitbox = {140, 90, 280, 80};
        _entityManager->getEntityList().back()->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_LEFT;
        i--;
    }
}

void Server::Enemy::generateBoss(void) {
    int i = (int) sqrt(getDifficulty()) + (rand() % findNumberPlayer());
    _entityManager->CreateEnemy(
        GameEngine::CONST_HEALTH * i * 10,
        GameEngine::CONST_DAMAGES,
        GameEngine::CONST_COOLDOWN + 700 - (i * 3 * rand() % (i * 10)),
        GameEngine::CONST_SPEED / 10,
        "",
        {(float)(rand() % 1000 + 980), (float)(rand() % 1080)}
    );
    
    _entityManager->getEntityList().back()->getComp<GameEngine::Hitbox>()->_hitbox = {140, 90, 280, 80};
    setRandDirrection(_entityManager->getEntityList().back());
}

void Server::Enemy::shoot(const std::shared_ptr<GameEngine::Entity>& entityShooting)
{
    uint16_t damages = entityShooting->getComp<GameEngine::Damages>()->_damages;
    uint16_t speed = GameEngine::CONST_SPEED / 2;
    Vector2 position = entityShooting->getComp<GameEngine::Position>()->getPosition();

    _entityManager->CreateRocket(damages, speed, "assets/bullet.png", position, false);
    _entityManager->getEntityList().back()->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_LEFT;
}

void Server::Enemy::move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction) {
    Vector2 pos = entity->getComp<GameEngine::Position>()
            ->getPosition();
    int speed = entity->getComp<GameEngine::Speed>()->_speed;
    speed += 1;
    int rand = std::rand() % 3;
    switch (direction) {
        case GameEngine::Actions::MOVE_LEFT:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x) - speed , static_cast<uint16_t>(pos.y) - rand / 2);
            break;
        case GameEngine::Actions::MOVE_RIGHT:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x) + speed, static_cast<uint16_t>(pos.y) + rand / 2);
            break;
        case GameEngine::Actions::MOVE_DOWN:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x) + rand / 2, static_cast<uint16_t>(pos.y) + speed);
            break;
        case GameEngine::Actions::MOVE_UP:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x) - rand / 2, static_cast<uint16_t>(pos.y) - speed);
            break;
        default:
            break;
    }
}

void Server::Enemy::isEnemyPositionValid(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Vector2 pos = entity->getComp<GameEngine::Position>()->getPosition();
    Rectangle hitbox = entity->getComp<GameEngine::Hitbox>()->_hitbox;
    GameEngine::Actions dirrection = entity->getComp<GameEngine::Position>()->_direction;

    if (pos.x <= 20) {
        entity->getComp<GameEngine::Position>()->setPosition(21, pos.y);
        changeDirrection(entity);
    }
    if (pos.x >= WINDOW_WIDTH - 200) {
        entity->getComp<GameEngine::Position>()->setPosition(WINDOW_WIDTH - 201, pos.y);
        changeDirrection(entity);
    }
    if (pos.y <= 20) {
        entity->getComp<GameEngine::Position>()->setPosition(pos.x, 21);
        changeDirrection(entity);
    }
    if (pos.y >= WINDOW_HEIGHT - 200) {
        entity->getComp<GameEngine::Position>()->setPosition(pos.x, WINDOW_HEIGHT - 201);
        changeDirrection(entity);
    } 
    move(entity, dirrection);
}

void Server::Enemy::changeDirrection(const std::shared_ptr<GameEngine::Entity>& entity)
{
    GameEngine::Actions dirrection = entity->getComp<GameEngine::Position>()->_direction;

    if (dirrection == GameEngine::Actions::MOVE_LEFT) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::Actions::MOVE_RIGHT;
    } else if (dirrection == GameEngine::Actions::MOVE_RIGHT) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::Actions::MOVE_LEFT;
    } else if (dirrection == GameEngine::Actions::MOVE_UP) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::Actions::MOVE_DOWN;
    } else if (dirrection == GameEngine::Actions::MOVE_DOWN) {
        entity->getComp<GameEngine::Position>()->_direction = GameEngine::Actions::MOVE_UP;
    }
}

int Server::Enemy::getDifficulty(void) const
{
    return _difficulty;
}

void Server::Enemy::setDifficulty(int difficulty)
{
    _difficulty = difficulty;
}

int Server::Enemy::getWave(void) const
{
    return _wave;
}

void Server::Enemy::setWave(int wave)
{
    _wave = wave;
}

bool Server::Enemy::getIsInGame(void) const
{
    return isInGame;
}

void Server::Enemy::setIsInGame(bool _isInGame)
{
    isInGame = _isInGame;
}
