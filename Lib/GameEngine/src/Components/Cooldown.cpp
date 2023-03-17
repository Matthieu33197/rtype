/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damages Component source file
*/

#include "../../include/Components/Cooldown.hpp"
#include "iostream"

GameEngine::Cooldown::Cooldown(int maxCooldownInMS)
: Component(GameEngine::TYPE_COOLDOWN)
{
    _maxCooldownInMS = maxCooldownInMS;
}

void GameEngine::Cooldown::startClock()
{
    _start = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
}

void GameEngine::Cooldown::endClock()
{
    _end = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
}

void GameEngine::Cooldown::setMaxCooldownInMS(int getMaxCooldownInMS)
{
    _maxCooldownInMS = getMaxCooldownInMS;
}

int GameEngine::Cooldown::getMaxCooldownInMS() const
{
    return _maxCooldownInMS;
}

bool GameEngine::Cooldown::isCooldownFinish()
{
    endClock();
    std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);

    if (time.count() >= _maxCooldownInMS) {
        startClock();
        return true;
    }
    else
        return false;
}