/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Player.cpp
*/

#include "../../include/Entities/Player.hpp"
#include "../../../Lib/GameEngine/include/Components/Health.hpp"
#include "../../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../../Lib/GameEngine/include/Components/Speed.hpp"
#include "../../../Lib/GameEngine/include/Components/Hitbox.hpp"
#include "../../../Lib/GameEngine/include/Components/Cooldown.hpp"

Server::Player::Player(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server)
: _entityManager(entityManager), _server(server)
{}


Server::Player::~Player() {
}

void Server::Player::sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::UPDATE_ENTITIES;
    messageUpdate << (entity->getComp<GameEngine::Health>()->_health);
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().y);
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().x);
    messageUpdate << static_cast<uint8_t>(entity->_type);
    messageUpdate << static_cast<uint32_t>(entity->_id);
    _server->notifiyClients(messageUpdate);
}

void Server::Player::run()
{
    checkPartylunsh();
    if (isInGame == true) {
        if (loseCondition() == true) {
            std::cout << "Game Over" << std::endl;
        }
        for (int i = 0; i < _playerList.size(); i++) {
            if (isPlayerDead(_playerList[i])) {
                continue;
            }
            for (int j = 0; j < _actionQueue[i].size(); j++) {
                if (_actionQueue[i][j] == GameEngine::SHOOT)
                    shoot(_playerList[i]);
                else {
                    if (isPositionValid(_playerList[i])) {
                        move(_playerList[i], _actionQueue[i][j]);
                    }
                }
                _actionQueue[i].erase(_actionQueue[i].begin() + j);
            }
            isPlayerTouchingEnemy(_playerList[i]);
        }
    }
}

void Server::Player::checkPartylunsh() {
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::ENEMY) {
            isInGame = true;
        }
    }
}

void Server::Player::isPlayerTouchingEnemy(const std::shared_ptr<GameEngine::Entity>& entity)
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::ENEMY) {
            
            if (entity->getComp<GameEngine::Position>()->getPosition().x >= entityList[i]->getComp<GameEngine::Position>()->getPosition().x - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && entity->getComp<GameEngine::Position>()->getPosition().x <= entityList[i]->getComp<GameEngine::Position>()->getPosition().x + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && entity->getComp<GameEngine::Position>()->getPosition().y >= entityList[i]->getComp<GameEngine::Position>()->getPosition().y - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2 
            && entity->getComp<GameEngine::Position>()->getPosition().y <= entityList[i]->getComp<GameEngine::Position>()->getPosition().y + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2) {
                entity->getComp<GameEngine::Health>()->_health = 0;
            }
        }
    }
}

bool Server::Player::loseCondition()
{
    int nbPlayer = 0;
    int count = 0;

    for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::PLAYER) {
            nbPlayer++;
            if (_entityManager->getEntityList()[i]->getComp<GameEngine::Health>()->_health >= 200) {
                _entityManager->getEntityList()[i]->getComp<GameEngine::Health>()->_health = 0;
            }
            if (_entityManager->getEntityList()[i]->getComp<GameEngine::Health>()->_health <= 0) {
                count++;
            }
        }
    }
    if (count == nbPlayer) {
        return true;
    } else {
        return false;
    }
}

bool Server::Player::isPlayerDead(const std::shared_ptr<GameEngine::Entity>& entity)
{
    if (entity->getComp<GameEngine::Health>()->_health <= 0 || entity->getComp<GameEngine::Health>()->_health >= 6000) {
        entity->getComp<GameEngine::Position>()->setPosition(3000, 3000);
        entity->getComp<GameEngine::Health>()->_health = 0;
        return true;
    }
    return false;
}

void Server::Player::popPlayer(int id)
{
    for (int i = 0; i < _playerList.size(); i++) {
        if (_playerList[i]->_id == id) {
            _playerList.erase(_playerList.begin() + i);
            return;
        }
    }
}

bool Server::Player::isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Vector2 pos = entity->getComp<GameEngine::Position>()->getPosition();
    Rectangle hitbox = entity->getComp<GameEngine::Hitbox>()->_hitbox;

    if (pos.x <= 20) {
        entity->getComp<GameEngine::Position>()->setPosition(21, pos.y);
        return false;
    }
    else if (pos.x >= WINDOW_WIDTH - 200) {
        entity->getComp<GameEngine::Position>()->setPosition(WINDOW_WIDTH - 201, pos.y);
        return false;
    }
    else if (pos.y <= 20 ) {
        entity->getComp<GameEngine::Position>()->setPosition(pos.x, 21);
        return false;
    }
    else if (pos.y >= WINDOW_HEIGHT - 200) {
        entity->getComp<GameEngine::Position>()->setPosition(pos.x, WINDOW_HEIGHT - 201);
        return false;
    } else {
        return true;
    }
}

void Server::Player::shoot(const std::shared_ptr<GameEngine::Entity>& entity)
{
    if (entity->getComp<GameEngine::Cooldown>()->isCooldownFinish()) {
        _entityManager->CreateRocket(
                GameEngine::CONST_DAMAGES,
                GameEngine::CONST_SPEED,
                "assets/Rocket.png",
                entity->getComp<GameEngine::Position>()->getPosition(),
                true);
        _entityManager->getEntityList().back()->getComp<GameEngine::Position>()->_direction = GameEngine::MOVE_RIGHT;

    }
}

void Server::Player::move(const std::shared_ptr<GameEngine::Entity>& entity, uint8_t direction) {
    Vector2 pos = entity->getComp<GameEngine::Position>()
            ->getPosition();
    int speed = entity->getComp<GameEngine::Speed>()->_speed;

    switch (direction) {
        case GameEngine::Actions::MOVE_LEFT:
            entity->getComp<GameEngine::Position>()->setPosition
            (static_cast<uint16_t>(pos.x) - speed, static_cast<uint16_t>(pos.y));
            break;
        case GameEngine::Actions::MOVE_RIGHT:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x) + speed, static_cast<uint16_t>(pos.y));
            break;
        case GameEngine::Actions::MOVE_DOWN:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x), static_cast<uint16_t>(pos.y) + speed);
            break;
        case GameEngine::Actions::MOVE_UP:
            entity->getComp<GameEngine::Position>()->setPosition
                    (static_cast<uint16_t>(pos.x), static_cast<uint16_t>(pos.y) - speed);
            break;
        default:
            break;
    }
}

void Server::Player::addPlayer(const std::shared_ptr<GameEngine::Entity> &newPlayer)
{
    _playerList.push_back(newPlayer);
    _actionQueue.emplace_back();
}