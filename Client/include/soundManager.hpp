/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs [SSH: noelito.freedynamicdns.org]
** File description:
** soundManager
*/

#ifndef SOUNDMANAGER_HPP_
#define SOUNDMANAGER_HPP_

#include <iostream>
#include "raylib.h"
#include "../../Lib/GameEngine/include/Utils/Musics.hpp"
#include "../../Lib/GameEngine/include/Utils/Sounds.hpp"

class SoundManager {
    public:
        SoundManager();
        ~SoundManager();
        void changeVolume(float volume);

        GameEngine::Musics MusicLobby;
        GameEngine::Sounds ButtonSound;
        GameEngine::Sounds BulletSound;
        GameEngine::Musics MusicGameplay;
        GameEngine::Sounds DeathEnemySound;
        GameEngine::Sounds StartGameSound;

        float _volume = 0.5;
    protected:
    private:
};


#endif /* !SOUNDMANAGER_HPP_ */
