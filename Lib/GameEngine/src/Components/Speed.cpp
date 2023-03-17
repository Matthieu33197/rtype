/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Speed.cpp
*/

#include "../../include/Components/Speed.hpp"

// Function that allows to initialize the speed of an entity
GameEngine::Speed::Speed(const uint16_t &speed)
: Component(GameEngine::TYPE_SPEED), _speed(speed)
{}
