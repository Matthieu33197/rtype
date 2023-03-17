/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Button.hpp
*/

#ifndef R_TYPE_BUTTON_HPP
#define R_TYPE_BUTTON_HPP

#include "raylib.h"
#include <cstdint>

namespace   GameEngine {
    //!  Button class
    /*!
      The purpose of this class is to manage the buttons of the game
    */
    class Button {
    public:
        //!  Button constructor
        /*!
          This function allows to initialize an button
        */
        Button();
        Button(const char *path);
        //!  Button destructor
        /*!
          This function allows to unload the texture of an button
        */
        ~Button();
        //!  drawButton function
        /*!
          This function allows to draw an button
        */
        void drawButton();
        //!  setposButton function
        /*!
          This function allows to set the position of an button
        */
        void setposButton(int x, int y);
        //!  getposButton function
        /*!
          This function allows to get the position of an button
        */
        Vector2 getposButton();
        //!  setTextureButton function
        /*!
          This function allows to choose a texture for an button
        */
        void setTextureButton(const char *path);
        //!  getTextureButton function
        /*!
          This function allows to get the current texture of an button
        */
        Texture2D getTextureButton();
        //!  _size variable
        /*!
          This variable allows to know the size of an button
        */
	   	void destroy();
        float _size;
    protected:
        //!  _button variable
        /*!
          This variable allows to know the texture of an button
        */
        Texture2D _button;
        //!  _pos variable
        /*!
          This variable allows to know the position of an button
        */
        Vector2 _pos;
    };
}

#endif //R_TYPE_BUTTON_HPP