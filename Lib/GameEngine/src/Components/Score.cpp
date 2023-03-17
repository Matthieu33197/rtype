/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Score source file
*/

#include "../../include/Components/Score.hpp"

GameEngine::Score::Score(const int &score)
: Component(GameEngine::TYPE_SCORE), _score(score)
{}
