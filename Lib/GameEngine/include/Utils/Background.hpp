/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Background.hpp
*/

#ifndef R_TYPE_BACKGROUND_HPP
#define R_TYPE_BACKGROUND_HPP

#include "raylib.h"
#include <cstdint>
#include <string>

namespace   GameEngine {
    //!  Background class
    /*!
      The purpose of this class is to manage the background of the game
    */
    class Background {
    public:
        //!  Background constructor
        /*!
          This function allows to initialize the background of the game
        */
        Background();
        Background(const std::string &path);
        //!  Background destructor
        /*!
          This function allows to unload the texture of the background
        */
        ~Background();
        //!  createBackground function
        /*!
          This function allows to create the background
        */
        void createBackground(const std::string &path);
        //!  drawBackground function
        /*!
          This function allows to draw the background
        */
        void drawBackground();
        //!  moveBackground function
        /*!
          This function allows to move the background
        */
        void moveBackground();
        //!  setposBackground function
        /*!
          This function allows to set the position of the background
        */
        void setposBackground(const int &x, const int &y);
        //!  getBackground function
        /*!
          This function allows to get the background
        */
        Texture2D getBackground() const;

        void setScale(const float &scale);

		void destroy();
    Vector2 _pos;
    private:
        //!  _background variable
        /*!
          This variable allows to know the background of the game
        */
        Texture2D _background;
        //!  _backgroundRect variable
        /*!
          This variable allows to know the background rectangle of the game
        */
        Rectangle _backgroundRect;
        //!  _speed variable
        /*!
          This variable allows to know the speed of the background
        */
        uint16_t _speed;
        //!  _pos variable
        /*!
          This variable allows to know the position of the background
        */
		std::string _path;
        //!  _scale variable
        /*!
          This variable allows to know the scale of the background
        */
        float _scale = 1.0;
    };
}

#endif //R_TYPE_BACKGROUND_HPP

