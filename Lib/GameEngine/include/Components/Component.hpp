/*
** EPITECH PROJECT, 2018
** R-Type
** File description:
** Component
*/

#ifndef ACOMPONENT_HPP_
#define ACOMPONENT_HPP_

#include "IComponent.hpp"

namespace GameEngine {
    //! Component class
    /*!
      The purpose of this class is to manage the components of the entities
    */
    class Component : public IComponent {
        public:
            //! Component constructor
            /*!
              This function allows to initialize the component
            */
            Component(const GameEngine::Type &type = GameEngine::TYPE_NOTHING);
            //! Component destructor
            /*!
              This function allows to destroy the component
            */
            ~Component() = default;
            //! getType function
            /*!
              This function allows to get the type of the entity
            */
            virtual GameEngine::Type getType() const override;
            //! setType function
            /*!
              This function allows to set the type of the entity
            */
            virtual void setType(const GameEngine::Type &newType) override;
        protected:
            //! _type variable
            /*!
              This variable contains the type of the entity
            */
            GameEngine::Type _type;                     // Type of entity
    };

}

#endif /* !ACOMPONENT_HPP_ */