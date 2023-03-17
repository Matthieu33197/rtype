/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Text.hpp
*/

#ifndef R_TYPE_TEXT_HPP
#define R_TYPE_TEXT_HPP

#include "raylib.h"
#include <cstdint>
#include <string>

namespace GameEngine {
    //!  Text class
    /*!
      The purpose of this class is to manage the text of the entities
    */
    class Text {
    public:
        //!  Text constructor
        /*!
          This function allows to initialize the text of an entity
        */
        Text();
        //!  Text destructor
        /*!
          This function allows to destroy the text of an entity
        */
        ~Text();
        //!  drawText function
        /*!
          This function allows to draw the text of an entity
        */
        void drawText();
        //!  setText function
        /*!
          This function allows to set the text of an entity
        */
        void setText(std::string text);
        //!  setposText function
        /*!
          This function allows to set the position of the text of an entity
        */
        void setposText(uint16_t x, uint16_t y);
        //!  getposText function
        /*!
          This function allows to get the position of the text of an entity
        */
        Vector2 getposText();
        //!  setFontSize function
        /*!
          This function allows to set the size of the text of an entity
        */
        void setFontSize(uint16_t size);
        //!  setFontColor function
        /*!
          This function allows to set the color of the text of an entity
        */
        void setFontColor(Color color);
        //!  setFont function
        /*!
          This function allows to set the font of the text of an entity
        */
        void setFont(std::string path);
        //!  setFontStyle function
        /*!
          This function allows to set the style of the text of an entity
        */
        void setFontStyle(uint16_t style);
    protected:
        //! font variable
        /*!
          This variable allows to know the font of the text of an entity
        */
        Font _font;
        //!  _color variable
        /*!
          This variable allows to know the color of the text of an entity
        */
        Color _color;
        //!  _size variable
        /*!
          This variable allows to know the size of the text of an entity
        */
        uint16_t _size;
        //!  _style variable
        /*!
          This variable allows to know the style of the text of an entity
        */
        uint16_t _style;
        //!  _pos variable
        /*!
          This variable allows to know the position of the text of an entity
        */
        Vector2 _pos;
        //!  _text variable
        /*!
          This variable allows to know the text of an entity
        */
        std::string _text;
    };
}

#endif //R_TYPE_TEXT_HPP