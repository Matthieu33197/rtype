/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Friendly Component
*/

#ifndef FRIENDLY_HPP_
#define FRIENDLY_HPP_

#include <utility>
#include <cstdint>
#include "Component.hpp"

namespace GameEngine {
    //!  Friendly class
    /*!
     The purpose of this class is to manage the Friendly component
    */
    class Friendly : public Component {
    public:
        //!  Friendly constructor
        /*!
         Pass in parameter the friendly variable\n
         The friendly variable is a boolean, if it's true the entity is friendly, if it's false the entity is not friendly\n
        */
        Friendly(const bool &friendly = false);
        //!  Friendly destructor
        /*!
         The destructor of the Friendly class
        */
        ~Friendly() = default;
        //!  isFriendly variable
        /*!
         The variable is a boolean, if it's true the entity is friendly, if it's false the entity is not friendly\n
        */
        bool isFriendly();
    private:
        //!  _friendly variable
        /*!
         The variable is a boolean, if it's true the entity is friendly, if it's false the entity is not friendly\n
        */
        bool _friendly;

    };
}

#endif /* !FRIENDLY_HPP_ */