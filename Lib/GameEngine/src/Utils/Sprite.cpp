/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** sprite.cpp
*/

#include "../../include/Utils/Sprite.hpp"
#include <iostream>


GameEngine::Sprite::Sprite(const char *path) {
    setTextureSprite(path);
    _spriteRect = {0.0f, 0.0f, (float)_sprite.width, (float)_sprite.height};
}

void GameEngine::Sprite::drawSprite() {
    DrawTexturePro(_sprite, _spriteRect, {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()}, {0, 0}, 0, WHITE);
}

Vector2 GameEngine::Sprite::getposSprite() {
    return { _spriteRect.x, _spriteRect.y };
}

void GameEngine::Sprite::setTextureSprite(const char *path) {
    _sprite = LoadTexture(path);
}

Texture2D GameEngine::Sprite::getTextureSprite() {
    return _sprite;
}

GameEngine::Sprite::~Sprite() {
    UnloadTexture(_sprite);
}

// Path: Server/src/GameEngine/Utils/sprite.cpp