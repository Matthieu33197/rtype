/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Position Component
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <utility>
#include "Component.hpp"
#include <cstdint>

namespace GameEngine {
    //! Position class
    /*!
      The purpose of this class is to manage the position of the entities
    */
    class Position : public Component {
    public:
        //! Position constructor
        /*!
          This function allows to initialize the position of an entity
        */
	    Position(const uint16_t &startX = CONST_POSX, const uint16_t &startY = CONST_POSY);
        //! Position destructor
        /*!
          This function allows to destroy the position of an entity
        */
        ~Position() = default;
        //! _positionY
        /*!
          This variable contains the position Y of an entity
        */
        uint16_t _positionY;
        //! _positionX
        /*!
          This variable contains the position X of an entity
        */
        uint16_t _positionX;
        //! _direction
        /*!
          This variable contains the direction of an entity
        */
        GameEngine::Actions _direction;
        //! setPosition function
        /*!
          This function allows to set the position of an entity
        */
        void setPosition(const uint16_t &newX, const uint16_t &newY);
        //! getPosition function
        /*!
          This function allows to get the position of an entity
        */
        Vector2 getPosition() const;
    private:
        //! _type variable
        /*!
          This variable contains the type of the entity
        */
    };
}

#endif /* !POSITION_HPP_ */