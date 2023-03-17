/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox Component source file
*/

#include "../../include/Components/Hitbox.hpp"
#include <iostream>

// Function that allows to initialize the Hitbox of an entity
GameEngine::Hitbox::Hitbox(const Rectangle &hitbox)
: Component(GameEngine::TYPE_HITBOX), _hitbox(hitbox)
{}
