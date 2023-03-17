/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Musics.hpp
*/

#ifndef R_TYPE_MUSIC_HPP
#define R_TYPE_MUSIC_HPP

#include "raylib.h"
#include <cstdint>
#include <string>

namespace GameEngine {

    class Musics
    {
    public:
        Musics();
        Musics(const std::string &path);
        ~Musics();

        void createMusic(const std::string &path);
        void playMusic();
        void stopMusic();
        void pauseMusic();
        void resumeMusic();
        void setVolumeMusic(const float &volume);
        void setPitchMusic(const float &pitch);
        void destroy();
        void updateMusicStream();

        Music getMusic() const;
    private:
        Music _music;
    };

}

#endif //R_TYPE_MUSIC_HPP