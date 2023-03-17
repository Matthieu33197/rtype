/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** entityHandler
*/

#include "../include/entityHandler.hpp"

EntityHandler::EntityHandler()
:_entityManager(std::make_unique<GameEngine::EntityManager>())
{

}

void EntityHandler::preLoadTextures(const std::string &playerSkin, const std::string &enemySkin)
{
	_playerSkin = _style.preloadTexture(playerSkin);
	_enemySkin = _style.preloadTexture(enemySkin);
	_rocketSkin = _style.preloadTexture("asset/bullet.png");
	_wall = _style.preloadTexture("asset/wall.png");
	_powerup = _style.preloadTexture("asset/powerup.png");
}

void EntityHandler::removeEntityId(const uint32_t &id)
{
	for (auto &ptr : _entityManager->getEntityList()) {
		if (ptr->_id == id) {
			_entityManager->popEntity(id);
		}
	}
}

int EntityHandler::updateEntity(CombOwnedMsg &owner)
{
    uint32_t id = 0;
	uint8_t type = 0;
	uint16_t posX= 0;
	uint16_t posY = 0;
	uint16_t health = 0;

	if (owner.msg.body.size() == sizeof(uint32_t) + sizeof(uint8_t) + (sizeof(uint16_t) * 3)) {
		owner.msg >> id;
		owner.msg >> type;
		owner.msg >> posX;
		owner.msg >> posY;
		owner.msg >> health;
	} else if (owner.msg.body.size() == sizeof(uint32_t) + sizeof(uint8_t) + (sizeof(uint16_t) * 2)) {
		owner.msg >> id;
		owner.msg >> type;
		owner.msg >> posX;
		owner.msg >> posY;
	} else {
		return 84;
	}

	Vector2 position = {static_cast<float>(posX), static_cast<float>(posY)};

	for (int i = 0; i < _entityManager->getEntityList().size(); i++) {
		if (_entityManager->getEntityList()[i]->_id == id) {
				_entityManager->getEntityList()[i]->getComp<GameEngine::Position>()->setPosition(posX, posY);
				if (_entityManager->getEntityList()[i]->hasComp<GameEngine::Health>())
					_entityManager->getEntityList()[i]->getComp<GameEngine::Health>()->_health = health;
				return 1;
			}
    }
	switch (type)
	{
	case GameEngine::PLAYER:
		_entityManager->CreatePlayer(health, 0, 0, "asset/spaceship.png", position);
		_entityManager->getEntityList().back()->getComp<GameEngine::Style>()->LoadLoadedTexture(_playerSkin);
		_entityManager->getEntityList().back()->_id = id;
		break;
	case GameEngine::ENEMY:
		_entityManager->CreateEnemy(health, 0, 0, 0, "asset/enemi1.png", position);
		_entityManager->getEntityList().back()->getComp<GameEngine::Style>()->LoadLoadedTexture(_enemySkin);
		_entityManager->getEntityList().back()->_id = id;
		break;
	case GameEngine::ROCKET:
		_entityManager->CreateRocket(0, 0, "asset/bullet.png", position, false);
		_entityManager->getEntityList().back()->getComp<GameEngine::Style>()->LoadLoadedTexture(_rocketSkin);
		_entityManager->getEntityList().back()->_id = id;
		break;
	case GameEngine::POWERUP:
		_entityManager->CreatePowerUp(0, "", position);
		_entityManager->getEntityList().back()->getComp<GameEngine::Style>()->LoadLoadedTexture(_powerup);
		_entityManager->getEntityList().back()->_id = id;
		break;
	case GameEngine::WALL:
		_entityManager->CreateWall(0, 0, 0, "", position);
		_entityManager->getEntityList().back()->getComp<GameEngine::Style>()->LoadLoadedTexture(_wall);
		_entityManager->getEntityList().back()->_id = id;
		break;
	default:
		return 84;
		break;
	}

	return 0;
}

int EntityHandler::removeEntity(CombOwnedMsg &owner)
{
    uint32_t id = 0;

	if (owner.msg.body.size() != sizeof(uint32_t))
		return 84;

    owner.msg >> id;
	removeEntityId(id);
    return 0;
}

int EntityHandler::moveEntity(CombOwnedMsg &owner)
{
    uint32_t entity_id = 0;
	int8_t x = 0;
	int8_t y = 0;

	if (owner.msg.body.size() != sizeof(uint32_t) + (sizeof(int8_t) * 2))
        return 84;

	owner.msg >> y;
	owner.msg >> x;
	owner.msg >> entity_id;
	for (auto &entity : _entityManager->getEntityList()) {
		if (entity->_id == entity_id)
			entity->getComp<GameEngine::Position>()->setPosition(x, y);
        return 1;
    }
    return 0;
}

EntityHandler::~EntityHandler()
{
	UnloadTexture(_playerSkin);
	UnloadTexture(_enemySkin);
	UnloadTexture(_rocketSkin);
	UnloadTexture(_wall);
	UnloadTexture(_powerup);
}
