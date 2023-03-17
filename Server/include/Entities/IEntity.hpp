/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** IEntity.hpp
*/

#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <vector>
#include <iostream>
#include "raylib.h"

//! IEntity interface
/*!
 IEntity is an interface. Every Entity like Player or Enemy must inherit.\n
 You can take a look too Player.hpp or Enemy.hpp to see how it works in details\n
*/
class IEntity {
public:
    virtual ~IEntity() = default;
    //! IEntity interface
    /*!
     You call run to do and manage all the things you want for your entity
    */
    virtual void run() = 0;
private:
};

#endif