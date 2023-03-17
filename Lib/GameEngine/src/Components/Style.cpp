/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Style.cpp
*/

#include "../../include/Components/Style.hpp"
#include "raylib.h"

// Function that allows to initialize the style of an entity
GameEngine::Style::Style(const std::string &path)
: Component(GameEngine::TYPE_STYLE), _path(path)
{}

GameEngine::Style::Style()
: Component(GameEngine::TYPE_STYLE), _path("")
{}

// Function which allow to change the current texturerect for make move sprite of an entity texture
void GameEngine::Style::updateTextureRect() {
    _textureRect.x += _textureRect.width;
    if (_textureRect.x >= _texture.width)
        _textureRect.x = 0;
}

Texture2D &GameEngine::Style::LoadMyTexture()
{
	std::cout << "path: " << _path << std::endl;
    _texture = LoadTexture(_path.c_str());
    _textureRect = {0.0f, 0.0f, (float)_texture.width/6, (float)_texture.height};

    return (_texture);
}

Texture2D &GameEngine::Style::LoadLoadedTexture(Texture2D texture)
{
    _texture = texture;
    _textureRect = {0.0f, 0.0f, (float)_texture.width/6, (float)_texture.height};

    return (_texture);
}

void GameEngine::Style::unloadMyTexture(Texture2D &texture)
{
    UnloadTexture(texture);
}

Texture2D &GameEngine::Style::preloadTexture(const std::string &file)
{
	std::cout << "path: " << file << std::endl;
    _texture = LoadTexture(file.c_str());

    return (_texture);
}

Rectangle GameEngine::Style::getTextureRect() const
{
    return(_textureRect);
}
