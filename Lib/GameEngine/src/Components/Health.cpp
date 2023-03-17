/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
**
*/
/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Health Component source file
*/

#include "../../include/Components/Health.hpp"

// Function that allows to initialize the health of an entity
GameEngine::Health::Health(const uint16_t &startHealth)
: Component(GameEngine::TYPE_HEALTH), _health(startHealth)
{}