/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position Component source file
*/

#include "../../include/Components/Position.hpp"

// Function that allows to initialize the position of an entity
GameEngine::Position::Position(const uint16_t &startPositionX, const uint16_t &startPositionY)
: Component(GameEngine::TYPE_POSITION), _positionX(startPositionX), _positionY(startPositionY),
 _direction(GameEngine::NOTHING)
{}

// Funciton which get the current position of an entity
Vector2 GameEngine::Position::getPosition() const
{
    Vector2 returnValue = {static_cast<float>(_positionX),
                           static_cast<float>(_positionY)};

    return (returnValue);
}

// Function which allows to choose the new position of an entity
void GameEngine::Position::setPosition(const uint16_t &newX, const uint16_t &newY)
{
    _positionX = newX;
    _positionY = newY;
}