/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Friendly source file
*/

#include "../../include/Components/Friendly.hpp"

GameEngine::Friendly::Friendly(const bool &friendly)
: Component(GameEngine::TYPE_FRIENDLY), _friendly(friendly)
{}

bool GameEngine::Friendly::isFriendly()
{
    return (_friendly);
}