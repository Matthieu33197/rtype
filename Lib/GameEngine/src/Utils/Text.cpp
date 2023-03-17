/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text.cpp
*/

#include "../../include/Utils/Text.hpp"
#include <iostream>


GameEngine::Text::Text() {
    _font = GetFontDefault();
    _color = BLACK;
    _size = 20;
    _style = 0;
    _pos = {0, 0};
    _text = " ";
}

void GameEngine::Text::drawText() {
    DrawTextEx(_font, _text.c_str(), _pos, _size, _style, _color);
}

void GameEngine::Text::setText(std::string text) {
    _text = text.c_str();
}

void GameEngine::Text::setposText(uint16_t x, uint16_t y) {
    _pos.x = x;
    _pos.y = y;
}

Vector2 GameEngine::Text::getposText() {
    return _pos;
}

void GameEngine::Text::setFontSize(uint16_t size) {
    _size = size;
}

void GameEngine::Text::setFontColor(Color color) {
    _color = color;
}

void GameEngine::Text::setFont(std::string path) {
    _font = LoadFont(path.c_str());
}

void GameEngine::Text::setFontStyle(uint16_t style) {
    _style = style;
}

GameEngine::Text::~Text() {
    UnloadFont(_font);
}

// Path: Server/src/GameEngine/Utils/Text.cpp