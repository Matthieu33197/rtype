/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs [SSH: noelito.freedynamicdns.org]
** File description:
** soundManager
*/


#include "../include/soundManager.hpp"

SoundManager::SoundManager()
{
    MusicLobby.createMusic("asset/Musics/MenuMusic.mp3");
    ButtonSound.createSound("asset/Musics/ButtonSound.mp3");
    BulletSound.createSound("asset/Musics/BulletSound2.wav");
    MusicGameplay.createMusic("asset/Musics/LevelMusic.mp3");
    DeathEnemySound.createSound("asset/Musics/DeathEnemie.wav");
    StartGameSound.createSound("asset/Musics/StartGame.wav");

    MusicLobby.setVolumeMusic(0.5);
    ButtonSound.setVolumeSound(0.5);
    BulletSound.setVolumeSound(0.5);
    MusicGameplay.setVolumeMusic(0.5);
    DeathEnemySound.setVolumeSound(0.5);
    StartGameSound.setVolumeSound(0.5);
}

void SoundManager::changeVolume(float volume)
{
    _volume = volume;
    MusicLobby.setVolumeMusic(volume);
    ButtonSound.setVolumeSound(volume);
    BulletSound.setVolumeSound(volume);
    MusicGameplay.setVolumeMusic(volume);
    DeathEnemySound.setVolumeSound(volume);
    StartGameSound.setVolumeSound(volume);
}

SoundManager::~SoundManager()
{
}