/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Background.cpp
*/

#include "../../include/Utils/Background.hpp"
#include <iostream>

GameEngine::Background::Background()
{
    _speed = 1;
}

GameEngine::Background::Background(const std::string &path)
{
	_path = path;
    createBackground(path.c_str());
    _speed = 1;
}

void GameEngine::Background::createBackground(const std::string &path)
{
	_path = path;
    _background = LoadTexture(path.c_str());
    _pos = {0.0, 0.0};
}

void GameEngine::Background::drawBackground()
{
    DrawTextureEx(_background, _pos, 0.0, _scale, WHITE);
}

void GameEngine::Background::moveBackground()
{
    _pos.x -= _speed;
    if (_pos.x <= -_background.width)
        _pos.x = _background.width;
}

void GameEngine::Background::setposBackground(const int &x, const int &y)
{
    _pos.x = x;
    _pos.y = y;
}

// Function that allows to get the background
Texture2D GameEngine::Background::getBackground() const
{
    return _background;
}

void GameEngine::Background::destroy()
{
	UnloadTexture(_background);
}

// Function that allows to unload the texture of an background
GameEngine::Background::~Background()
{}

void GameEngine::Background::setScale(const float &scale)
{
    _scale = scale;
}



// Path: Server/src/GameEngine/Utils/Background.cpp