/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damages Component source file
*/

#include "../../include/Components/Damages.hpp"


// Function that allows to initialize the damage of an entity
GameEngine::Damages::Damages(const uint16_t &startDamages)
: Component(GameEngine::TYPE_DAMAGES), _damages(startDamages)
{}
