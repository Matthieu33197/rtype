/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Rocket.cpp
*/

#include "../../include/Entities/Player.hpp"
#include "../../include/Entities/Rocket.hpp"
#include "../../../Lib/GameEngine/include/Components/Position.hpp"
#include "../../../Lib/GameEngine/include/Components/Speed.hpp"
#include "../../../Lib/GameEngine/include/Components/Friendly.hpp"
#include "../../../Lib/GameEngine/include/Components/Hitbox.hpp"
#include "../../../Lib/GameEngine/include/Components/Damages.hpp"
#include "../../../Lib/GameEngine/include/Components/Health.hpp"
#include "../../include/utils/unloadId.hpp"

Server::Rocket::Rocket(std::shared_ptr<GameEngine::EntityManager> &entityManager, std::shared_ptr<Network::ServerData<Network::Codes>> &server)
{
    _entityManager = entityManager;
    _server = server;
}

Server::Rocket::~Rocket() 
{
}

void Server::Rocket::run() 
{
    for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
        if (_entityManager->getEntityList()[i]->_type == GameEngine::ROCKET) {
        auto myRocket = _entityManager->getEntityList()[i];
        if (isPositionValid(myRocket) == false) {
            sendMessageUnloadID(myRocket->_id, _server);
            _entityManager->popEntity(myRocket->_id);
            continue;
        }
        if (myRocket->getComp<GameEngine::Friendly>()->isFriendly() == true) {
            isHittingEnemy(myRocket);
        } else {
            isHittingPlayer(myRocket);
        }
        move(myRocket, myRocket->getComp<GameEngine::Position>()->_direction);
    }
    }
}

void Server::Rocket::sendUpdateMessage(const std::shared_ptr<GameEngine::Entity>& entity)
{
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::UPDATE_ENTITIES;
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().y);
    messageUpdate << static_cast<uint16_t>(entity->getComp<GameEngine::Position>()->getPosition().x);
    messageUpdate << static_cast<uint8_t>(entity->_type);
    messageUpdate << static_cast<uint32_t>(entity->_id);
    _server->notifiyClients(messageUpdate);
}

void Server::Rocket::isHittingPlayer(const std::shared_ptr<GameEngine::Entity>& myRocket) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::PLAYER ) {
            if (myRocket->getComp<GameEngine::Position>()->getPosition().x >= entityList[i]->getComp<GameEngine::Position>()->getPosition().x - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().x <= entityList[i]->getComp<GameEngine::Position>()->getPosition().x + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().y >= entityList[i]->getComp<GameEngine::Position>()->getPosition().y - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().y <= entityList[i]->getComp<GameEngine::Position>()->getPosition().y + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2) {
                entityList[i]->getComp<GameEngine::Health>()->_health -= myRocket->getComp<GameEngine::Damages>()->_damages;
                if (entityList[i]->getComp<GameEngine::Health>()->_health < 0) {
                    entityList[i]->getComp<GameEngine::Health>()->_health = 0;
                }
                sendMessageUnloadID(myRocket->_id, _server);
                _entityManager->popEntity(myRocket->_id);
            }
        }
    }
}

void Server::Rocket::isHittingEnemy(const std::shared_ptr<GameEngine::Entity>& myRocket) 
{
    std::vector<std::shared_ptr<GameEngine::Entity>> entityList = _entityManager->getEntityList();
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i]->_type == GameEngine::EntityType::ENEMY) {
            if (myRocket->getComp<GameEngine::Position>()->getPosition().x >= entityList[i]->getComp<GameEngine::Position>()->getPosition().x - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().x <= entityList[i]->getComp<GameEngine::Position>()->getPosition().x + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.x / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().y >= entityList[i]->getComp<GameEngine::Position>()->getPosition().y - entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2 
            && myRocket->getComp<GameEngine::Position>()->getPosition().y <= entityList[i]->getComp<GameEngine::Position>()->getPosition().y + entityList[i]->getComp<GameEngine::Hitbox>()->_hitbox.y / 2) {
                entityList[i]->getComp<GameEngine::Health>()->_health -= myRocket->getComp<GameEngine::Damages>()->_damages;
                sendMessageUnloadID(myRocket->_id, _server);
                _entityManager->popEntity(myRocket->_id);
            }   
        }
    }
}


bool Server::Rocket::isPositionValid(const std::shared_ptr<GameEngine::Entity>& entity) 
{
    if (entity->getComp<GameEngine::Position>()->getPosition().x < 0 ||
        entity->getComp<GameEngine::Position>()->getPosition().x > WINDOW_WIDTH ||
        entity->getComp<GameEngine::Position>()->getPosition().y < 0 ||
        entity->getComp<GameEngine::Position>()->getPosition().y > WINDOW_HEIGHT) {
            return false;
    }
    return true;
}

void Server::Rocket::move(const std::shared_ptr<GameEngine::Entity>& myRocket, uint8_t direction) 
{   
    int speed = myRocket->getComp<GameEngine::Speed>()->_speed;
    int actualXPos = myRocket->getComp<GameEngine::Position>()->getPosition().x;
    int actualYPos = myRocket->getComp<GameEngine::Position>()->getPosition().y;

    if (direction == GameEngine::MOVE_LEFT)
        myRocket->getComp<GameEngine::Position>()->setPosition(actualXPos - speed, actualYPos);
    else if (direction == GameEngine::MOVE_RIGHT)
        myRocket->getComp<GameEngine::Position>()->setPosition(actualXPos + speed, actualYPos);
    else if (direction == GameEngine::MOVE_UP)
        myRocket->getComp<GameEngine::Position>()->setPosition(actualXPos, actualYPos - speed);
    else if (direction == GameEngine::MOVE_DOWN)
        myRocket->getComp<GameEngine::Position>()->setPosition(actualXPos, actualYPos + speed);
}