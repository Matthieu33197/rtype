/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
**
*/

#ifndef STYLE_HPP_
#define STYLE_HPP_

#include "raylib.h"
#include "Component.hpp"
#include <string>
#include <iostream>
#include <utility>

namespace GameEngine {
    //!  Style class
    /*!
      The purpose of this class is to manage the style of the entities
    */
    class Style : public Component{
    public:
        //!  Style constructor
        /*!
          This function allows to initialize the style of an entity
        */
        Style(const std::string &path);
        //!  Style constructor
        /*!
          This function allows to initialize the style of an entity
        */
        Style();
        //!  ~Style destructor
        /*!
          This function allows to destroy the style of an entity
        */
        ~Style() = default;
        //!  updateTextureRect function
        /*!
          This function allows to change the current texturerect for make move sprite of an entity texture
        */
        void updateTextureRect();
        //!  LoadMyTexture function
        /*!
          This function allows to load the texture of an entity
        */
        Texture2D &LoadMyTexture();
        //!  preloadTexture function
        /*!
          This function allows to preload the texture of an entity
        @param file is the path of the texture
         */
        Texture2D &preloadTexture(const std::string &file);
        //!  LoadLoadedTexture function
        /*!
          This function allows to load the texture of an entity
          @param texture is the texture of the entity
         */
        Texture2D &LoadLoadedTexture(Texture2D texture);
        //!  unloadMyTexture function
        /*!
          This function allows to unload the texture of an entity
           @param texture is the texture of the entity
         */
        void unloadMyTexture(Texture2D &texture);
        //!  getTexture function
        /*!
          This function allows to get the texture of an entity
        */
        Rectangle getTextureRect() const;
        //!  _path variable
        /*!
          This variable allows to know where is the asset of the entity
        */
        std::string _path;
        //!  _texture variable
        /*!
          This variable allows to know the texture of the entity
        */
        Texture2D _texture;
                //!  _textureRect variable
        /*!
          This variable allows to know the texture rect of the entity
        */
        Rectangle _textureRect;
    };
}

#endif /* !STYLE_HPP_ */