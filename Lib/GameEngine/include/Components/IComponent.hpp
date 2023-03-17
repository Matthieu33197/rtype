/*
** EPITECH PROJECT, 2018
** R-Type
** File description:
** IComponent
*/

#ifndef ICOMPONENT_HPP_
#define ICOMPONENT_HPP_

#include "../Constants.hpp"

namespace GameEngine {
    //! IComponent class
    /*!
      The purpose of this class is to manage the components of the entities
    */
    class IComponent {
        public:
            //! Icomponent destructor
            /*!
              The purpose of this destructor is to delete the IComponent
            */
            virtual ~IComponent() = default;
            //! getType function
            /*!
              The purpose of this function is to get the type of the component
            */
            virtual GameEngine::Type getType() const = 0;
            //! setType function
            /*!
              The purpose of this function is to set the type of the component
            */
            virtual void setType(const GameEngine::Type &type) = 0;
        protected:
    };

}

#endif /* !ICOMPONENT_HPP_ */