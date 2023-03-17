/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Score Component
*/

#ifndef SCORE_HPP_
#define SCORE_HPP_

#include <utility>
#include "Component.hpp"
#include <cstdint>

namespace GameEngine {
    //!  Score class
    /*!
     The purpose of this class is to manage the Score of the player
    */
    class Score : public Component {
    public:
        //!  Score constructor
        /*!
         Pass in parameter the score of the player
        */
        Score(const int &score = 0);
        //!  Score destructor
        /*!
         Delete the Score component
        */
        ~Score() = default;
        //! _score variable
        /*!
         The score of the player
        */
        uint32_t _score;
    };
}

#endif /* !SCORE_HPP_ */