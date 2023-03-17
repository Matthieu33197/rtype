/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
**
*/

#ifndef SPEED_HPP_
#define SPEED_HPP_

#include <cstdint>
#include "raylib.h"
#include "Component.hpp"

namespace GameEngine {
    //! Speed class
    /*!
      The purpose of this class is to manage the speed of the entities
    */
    class Speed : public Component {
    public:
        //! Speed constructor
        /*!
          This function allows to initialize the speed of an entity
        */
        Speed(const uint16_t &speed = CONST_SPEED);
        //! Speed destructor
        /*!
          This function allows to destroy the speed of an entity
        */
        ~Speed() = default;
        //! _speed
        /*!
          This variable contains the speed of an entity
        */
        uint16_t _speed;
    };
}

#endif /* !SPEED_HPP_ */
