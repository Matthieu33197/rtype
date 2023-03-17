/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sounds.hpp
*/

#ifndef R_TYPE_SOUNDS_HPP
#define R_TYPE_SOUNDS_HPP

#include "raylib.h"
#include <cstdint>
#include <string>

namespace GameEngine {

    class Sounds
    {
    public:
        Sounds();
        Sounds(const std::string &path);
        ~Sounds();

        void createSound(const std::string &path);
        void playSound();
        void stopSound();
        void pauseSound();
        void resumeSound();
        void setVolumeSound(const float &volume);
        void setPitchSound(const float &pitch);
        void destroy();

        Sound getSound() const;
    private:
        Sound _sound;
    };

}

#endif //R_TYPE_SOUNDS_HPP