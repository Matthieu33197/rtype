/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Musics.cpp
*/

#include "../../include/Utils/Musics.hpp"

GameEngine::Musics::Musics() {
}

GameEngine::Musics::Musics(const std::string &path) {
    createMusic(path);
}

GameEngine::Musics::~Musics() {
}

void GameEngine::Musics::createMusic(const std::string &path) {
    _music = LoadMusicStream(path.c_str());
}

void GameEngine::Musics::playMusic() {
    PlayMusicStream(_music);
}

void GameEngine::Musics::stopMusic() {
    StopMusicStream(_music);
}

void GameEngine::Musics::pauseMusic() {
    PauseMusicStream(_music);
}

void GameEngine::Musics::resumeMusic() {
    ResumeMusicStream(_music);
}

void GameEngine::Musics::setVolumeMusic(const float &volume) {
    SetMusicVolume(_music, volume);
}

void GameEngine::Musics::setPitchMusic(const float &pitch) {
    SetMusicPitch(_music, pitch);
}

void GameEngine::Musics::destroy() {
    UnloadMusicStream(_music);
}

Music GameEngine::Musics::getMusic() const {
    return _music;
}

void GameEngine::Musics::updateMusicStream() {
    UpdateMusicStream(_music);
}


// Path: Lib/GameEngine/src/Utils/Musics.cpp