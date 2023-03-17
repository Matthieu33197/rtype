/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** AComponent source file
*/

#include "../../include/Components/Component.hpp"

GameEngine::Component::Component(const GameEngine::Type &type)
: _type(type)
{}

// Function which allows to give the type of the entity
GameEngine::Type GameEngine::Component::getType() const
{
    return _type;
}

// Function which allows to choose the type of the entity
void GameEngine::Component::setType(const GameEngine::Type &newType)
{
    _type = newType;
}