/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Health Component
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

#include "Component.hpp"
#include <cstdint>

namespace GameEngine {
    //! Health class
    /*!
      The purpose of this class is to manage the health of the entities
    */
    class Health : public Component {
        public:
            //! Health constructor
            /*!
              This function allows to initialize the health of an entity
            */
            Health(const uint16_t &health = CONST_HEALTH);
            //! Health destructor
            /*!
              This function allows to destroy the health of an entity
            */
            ~Health() = default;
            //! _health
            /*!
              This variable contains the health of an entity
            */
            uint16_t _health;
    };
}

#endif /* !HEALTH_HPP_ */