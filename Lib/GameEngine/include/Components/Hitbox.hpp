/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Hitbox Component
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <utility>
#include "Component.hpp"

namespace GameEngine {
    //! Hitbox class
    /*!
      The purpose of this class is to manage the hitbox of the entities
    */
    class Hitbox : public Component{
    public:
        //! Hitbox constructor
        /*!
          This function allows to initialize the Hitbox of an entity
        */

        Hitbox(const Rectangle &hitbox = {0, 0, 0, 0});
        //! Hitbox destructor
        /*!
          This function allows to destroy the Hitbox of an entity
        */
        ~Hitbox() = default;
        //! _hitbox
        /*!
          This variable contains the Hitbox of an entity
        */
        Rectangle _hitbox;
    };
}

#endif /* !HITBOX_HPP_ */