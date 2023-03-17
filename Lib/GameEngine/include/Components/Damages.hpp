/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Damages Component
*/

#ifndef DAMAGES_HPP_
#define DAMAGES_HPP_

#include <utility>
#include <cstdint>
#include "Component.hpp"

namespace GameEngine {
    //! Damages class
    /*!
      The purpose of this class is to manage the damages of the entities
    */
    class Damages : public Component {
    public:
        //! Damages constructor
        /*!
          This function allows to initialize the damages of an entity
        */
        Damages(const uint16_t &startDamages = CONST_DAMAGES);
        //! Damages destructor
        /*!
          This function allows to destroy the damages of an entity
        */
        ~Damages() = default;
        //! _damages
        /*!
          This variable contains the damages of an entity
        */
        uint16_t _damages;
    };
}

#endif /* !DAMAGES_HPP_ */