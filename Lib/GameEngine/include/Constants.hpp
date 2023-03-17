/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Constants.hpp
*/

#include "raylib.h"

namespace GameEngine {
    #define WINDOW_WIDTH 1920
    #define WINDOW_HEIGHT 1080
    #define MINIMUM_PLAYER 2
    enum Constants {
        CONST_HEALTH = 100,
        CONST_DAMAGES = 50,
        CONST_SPEED = 10,
        CONST_POSY = 0,
        CONST_POSX = 0,
        CONST_COOLDOWN = 100,
    };
    enum Type {
        TYPE_HEALTH,
        TYPE_POSITION,
        TYPE_DAMAGES,
        TYPE_HITBOX,
        TYPE_FRIENDLY,
        TYPE_SCORE,
        TYPE_SPEED,
        TYPE_STYLE,
		TYPE_NOTHING,
        TYPE_COOLDOWN,
    };
    enum Actions {
        MOVE_LEFT,
        MOVE_RIGHT,
        MOVE_UP,
        MOVE_DOWN,
        SHOOT,
        NOTHING,
    };
    enum EntityType {
        PLAYER,
        ENEMY,
        ROCKET,
        POWERUP,
        WALL,
    };
}