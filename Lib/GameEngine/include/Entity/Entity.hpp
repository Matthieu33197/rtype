/*
** EPITECH PROJECT, 2018
** R-Type
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <list>
#include <algorithm>
#include <type_traits>
#include <iostream>
#include "../Components/Component.hpp"

namespace GameEngine {
    //!  Entity class
    /*!
      The purpose of this class is to manage the components of an Entity.\n
      In this class we can add new components in order to personalize an Entity\n
      The goal is also to be able to store the components of this entity in: _componentList.\n
    */
    class Entity {
    public:
        //! Entity constructor
        /*!
         The constructor Entity\n
         Here we just need an ID that gonna be store in this class. This ID need to IDentify the Entity\n
         @param id the ID of the Entity
         */
        Entity(int id);
        //! ~Entity destructor
        /*!
         The destructor Entity\n
         */
        ~Entity();
        //! addComp function
        /*!
         Add a component to this Entity\n
         You can add a new Health component like this for example (look EntityManager.cpp)\n
         The component: std::shared_ptr<GameEngine::Damages> damagesComponent = std::make_shared<GameEngine::Damages>(damages)\n
         Add the component: playerEntity->addComp<GameEngine::Health>(healthComponent)\n
         */
        template <class T>
        void addComp(std::shared_ptr<T> &Component)
        {
            _componentList.push_back(Component);
        }
        //! getComp function
        /*!
         Get a component (to then retrieve his value)\n
         It return a shared pointer on this component.\n
         You can retrieve the value of the Health Component like this: ENTITY->getComp<GameEngine::Health>()->_health\n
         */
        template <class T>
        std::shared_ptr<T> getComp()
        {
            T Component;

            for (auto &it: _componentList)
                if (it->getType() == Component.getType())
				    return std::dynamic_pointer_cast<T>(it);
            return nullptr;
        }
        //! hasComp function
        /*!
         Check if this Entity have a component\n
         It return a boolean\n
        */
        template <class T>
        bool hasComp() noexcept
        {
            T Comp;

            for (auto &comp : _componentList) {
                if (comp->getType() == Comp.getType())
                    return true;
            }
            return false;
        }
        //! _type variable
        /*!
         The type of this Entity (is it a Player, a Monster, a Rocket)\n
         Look the type in Constant.hpp -> Type\n
        */
        GameEngine::EntityType _type;
        //! _id variable
        /*!
         The identifier integer of this Entity\n
        */
        uint32_t _id;

    private:
        //! _componentList variable
        /*!
         The list of all the component in this Entity\n
         It's a list of shared pointer on the Component Class\n
         You can access to the value of a component with getComp see above\n
        */
        std::list<std::shared_ptr<Component>> _componentList;
    };
}

#endif /* !ENTITY_HPP_ */