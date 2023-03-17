/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sounds.cpp
*/

#include "../../include/Utils/Sounds.hpp"

GameEngine::Sounds::Sounds() {
}

GameEngine::Sounds::Sounds(const std::string &path) {
    createSound(path);
}

GameEngine::Sounds::~Sounds() {
}

void GameEngine::Sounds::createSound(const std::string &path) {
    _sound = LoadSound(path.c_str());
}

void GameEngine::Sounds::playSound() {
    PlaySoundMulti(_sound);
}

void GameEngine::Sounds::stopSound() {
    StopSound(_sound);
}

void GameEngine::Sounds::pauseSound() {
    PauseSound(_sound);
}

void GameEngine::Sounds::resumeSound() {
    ResumeSound(_sound);
}

void GameEngine::Sounds::setVolumeSound(const float &volume) {
    SetSoundVolume(_sound, volume);
}

void GameEngine::Sounds::setPitchSound(const float &pitch) {
    SetSoundPitch(_sound, pitch);
}

void GameEngine::Sounds::destroy() {
    UnloadSound(_sound);
}

Sound GameEngine::Sounds::getSound() const {
    return _sound;
}