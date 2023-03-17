/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Button.cpp
*/

#include "../../include/Utils/Button.hpp"
#include <iostream>

GameEngine::Button::Button() {

}

GameEngine::Button::Button(const char *path) {
    setTextureButton(path);
}

void GameEngine::Button::drawButton() {
    DrawTextureEx(_button, {_pos.x, _pos.y}, 0, _size, WHITE);
}

Vector2 GameEngine::Button::getposButton() {
    return _pos;
}

void GameEngine::Button::setTextureButton(const char *path) {
    _button = LoadTexture(path);
}

Texture2D GameEngine::Button::getTextureButton() {
    return _button;
}

void GameEngine::Button::destroy()
{
	UnloadTexture(_button);
}

GameEngine::Button::~Button() {
}

void GameEngine::Button::setposButton(int x, int y) {
    _pos.x = x;
    _pos.y = y;
}

// Path: Server/src/GameEngine/Utils/Button.cpp