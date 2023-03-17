/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** PowerUp.cpp
*/

#include "../../include/Entities/Player.hpp"
#include "../../include/Entities/PowerUp.hpp"
#include "../../../Lib/GameEngine/include/Components/Health.hpp"
#include "../../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../../Lib/GameEngine/include/Components/Speed.hpp"
#include "../../../Lib/GameEngine/include/Components/Hitbox.hpp"
#include "../../../Lib/GameEngine/include/Components/Damages.hpp"
#include "../../../Lib/GameEngine/include/Components/Cooldown.hpp"
#include "../../include/utils/unloadId.hpp"

Server::PowerUp::PowerUp(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server)
{
    _entityManager = entityManager;
    _score = 0;
    _server = server;
}

Server::PowerUp::~PowerUp() 
{
}

void Server::PowerUp::run() 
{
    for(int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::POWERUP) {
            auto ptr = _entityManager->getEntityList()[i];
            if (playerDropPowerUp(ptr) == true) {
                continue;
            } 
            if (isPositionValid(ptr) == true) {
                move(ptr, ptr->getComp<GameEngine::Position>()->_direction);
            } else {
                popPowerUp(ptr);
            }
        }
    }
}

int Server::PowerUp::countPowerUp() 
{
    int count = 0;
    for(int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::POWERUP) {
            count++;
        }
    }
    return count;
}

void Server::PowerUp::popPowerUp(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    sendMessageUnloadID(entity->_id, _server);
    _entityManager->popEntity(entity->_id);
}

void Server::PowerUp::move(const std::shared_ptr<GameEngine::Entity>& entity, const uint8_t direction) 
{
    Vector2 pos = entity->getComp<GameEngine::Position>()
            ->getPosition();
    int speed = 1;
    entity->getComp<GameEngine::Position>()->setPosition
    (static_cast<uint16_t>(pos.x) - speed, static_cast<uint16_t>(pos.y));
}

bool Server::PowerUp::isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    Vector2 pos = entity->getComp<GameEngine::Position>()->getPosition();
    if (pos.x < 0 || pos.x > WINDOW_HEIGHT || pos.y < 0 || pos.y > WINDOW_WIDTH) {
        popPowerUp(entity);
        return false;
    }
    move(entity, entity->getComp<GameEngine::Position>()->_direction);
    return true;
}

bool Server::PowerUp::playerDropPowerUp(const std::shared_ptr<GameEngine::Entity>& powerUp) {
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER) {
            if (powerUp->getComp<GameEngine::Position>()->getPosition().x >= entityList[i]->getComp<GameEngine::Position>()->getPosition().x - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && powerUp->getComp<GameEngine::Position>()->getPosition().x <= entityList[i]->getComp<GameEngine::Position>()->getPosition().x + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && powerUp->getComp<GameEngine::Position>()->getPosition().y >= entityList[i]->getComp<GameEngine::Position>()->getPosition().y - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2 
            && powerUp->getComp<GameEngine::Position>()->getPosition().y <= entityList[i]->getComp<GameEngine::Position>()->getPosition().y + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2) {
                int r = rand() % 8 + 1;
                applyPowerUp(entityList[i], r);
                _score += 5;
                popPowerUp(powerUp);
                return true;
            }
        }
    }   
    return false;
}

void Server::PowerUp::applyPowerUp(const std::shared_ptr<GameEngine::Entity>& entity, int v2) 
{
    switch (v2) {
        case 1:
        std::cout << "restoreHealth" << std::endl;
            restoreHealth(entity);
            break;
        case 2:
        std::cout << "restoreTeamHealth" << std::endl;
            restoreTeamHealth(entity);
            break;
        case 3:
        std::cout << "buffSpeed" << std::endl;
            buffSpeed(entity);
            break;
        case 4:
        std::cout << "buffTeamSpeed" << std::endl;
            buffTeamSpeed(entity);
            break;
        case 5:
        std::cout << "buffDamages" << std::endl;
            buffDamages(entity);
            break;
        case 6:
        std::cout << "buffTeamDamages" << std::endl;
            buffTeamDamages(entity);
            break;
        case 7:
        std::cout << "buffFireRate" << std::endl;
            buffFireRate(entity);
            break;
        case 8:
        std::cout << "buffTeamFireRate" << std::endl;
            buffTeamFireRate(entity);
            break;
        default:
            break;
    }
}

void Server::PowerUp::sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::UPDATE_ENTITIES;
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().y);
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().x);
    messageUpdate << static_cast<uint8_t>(entity->_type);
    messageUpdate << static_cast<uint32_t>(entity->_id);
    _server->notifiyClients(messageUpdate);
}

void Server::PowerUp::restoreHealth(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    entity->getComp<GameEngine::Health>()->_health = GameEngine::CONST_HEALTH;
}
void Server::PowerUp::restoreTeamHealth(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER ) {
            if (entityList[i]->getComp<GameEngine::Health>()->_health <= 0) {
                std::cout << "retours a la vie !" << std::endl;
                uint16_t x = rand () % 1000 + 1;
                uint16_t y = rand () % 1000 + 1;
                entityList[i]->getComp<GameEngine::Position>()->setPosition(x, y);
            }
            restoreHealth(entityList[i]);
        }
    }
}

void Server::PowerUp::buffSpeed(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    entity->getComp<GameEngine::Speed>()->_speed += 1;
}

void Server::PowerUp::buffTeamSpeed(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER ) {
            entityList[i]->getComp<GameEngine::Speed>()->_speed += 1 / 2;
        }
    }
}

void Server::PowerUp::buffDamages(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    entity->getComp<GameEngine::Damages>()->_damages += 10;
}

void Server::PowerUp::buffTeamDamages(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER ) {
            entityList[i]->getComp<GameEngine::Damages>()->_damages += 5;
        }
    }
}

void Server::PowerUp::buffFireRate(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    entity->getComp<GameEngine::Cooldown>()->setMaxCooldownInMS(entity->getComp<GameEngine::Cooldown>()->getMaxCooldownInMS() - 7);
}

void Server::PowerUp::buffTeamFireRate(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER ) {
            entity->getComp<GameEngine::Cooldown>()->setMaxCooldownInMS(entity->getComp<GameEngine::Cooldown>()->getMaxCooldownInMS() - 3);
        }
    }
}