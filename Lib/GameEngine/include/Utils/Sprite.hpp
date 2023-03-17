/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Sprite.hpp
*/

#ifndef R_TYPE_SPRITE_HPP
#define R_TYPE_SPRITE_HPP

#include "raylib.h"
#include <cstdint>

namespace   GameEngine {
    //!  Sprite class
    /*!
      The purpose of this class is to manage the sprites of the entities
    */
    class Sprite {
    public:
        //!  Sprite constructor
        /*!
          This function allows to initialize the sprite of an entity
        */
        Sprite(const char *path);
        //!  Sprite destructor
        /*!
          This function allows to unload the sprite of an entity
        */
        ~Sprite();
        //!  drawSprite function
        /*!
          This function allows to draw the sprite of an entity
        */
        void drawSprite();
        //!  setposSprite function
        /*!
          This function allows to set the position of the sprite of an entity
        */
        void setposSprite(uint16_t x, uint16_t y);
        //!  getposSprite function
        /*!
          This function allows to get the position of the sprite of an entity
        */
        Vector2 getposSprite();
        //!  setTextureSprite function
        /*!
          This function allows to choose a texture for the sprite of an entity
        */
        void setTextureSprite(const char *path);
        //!  getTextureSprite function
        /*!
          This function allows to get the current texture of the sprite of an entity
        */
        Texture2D getTextureSprite();
    protected:
        //!  _sprite variable
        /*!
          This variable allows to know the texture of the sprite of an entity
        */
        Texture2D _sprite;
        //!  _spriteRect variable
        /*!
          This variable allows to know the rectangle of the sprite of an entity
        */
        Rectangle _spriteRect;
    };
}

#endif //R_TYPE_SPRITE_HPP