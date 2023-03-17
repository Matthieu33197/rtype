/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** Cooldown Component
*/

#ifndef COOLDOWN_HPP_
#define COOLDOWN_HPP_

#include <utility>
#include <cstdint>
#include "Component.hpp"
#include <chrono>


namespace GameEngine {
    //!  Cooldown class
    /*!
     The purpose of this class is to manage the Cooldown component
    */
    class Cooldown : public Component {
        public:
            //!  Cooldown constructor
            /*!
                This function allows to initialize the Cooldown component
                @param maxCooldownInMS : the max cooldown in ms
            */
            Cooldown(int maxCooldownInMS = CONST_COOLDOWN);
            //!  Cooldown destructor
            /*!
                This function allows to destroy the Cooldown component
            */
            ~Cooldown() = default;
            //!  startClock function
            /*!
                This function allows to start the clock
            */
            void startClock();
            //!  endClock function
            /*!
                This function allows to end the clock
            */
            void endClock();
            //!  getElapsedTimeInMS function
            /*!
                This function allows to get the elapsed time in ms
                @return the elapsed time in ms
            */
            bool isCooldownFinish();
            //!  setMaxCooldownInMS function
            /*!
                This function allows to set the max cooldown in ms
                @param maxCooldownInMS : the max cooldown in ms
            */
            void setMaxCooldownInMS(int maxCooldownInMS);
            //!  getMaxCooldownInMS function
            /*!
                This function allows to get the max cooldown in ms
                @return the max cooldown in ms
            */
            int getMaxCooldownInMS() const;
        private:
        //!  _start variable
        /*!
            This variable contains the start time
        */
        std::chrono::time_point<std::chrono::system_clock> _start;
        //!  _end variable
        /*!
            This variable contains the end time
        */
        std::chrono::time_point<std::chrono::system_clock> _end;
        //!  _maxCooldownInMS variable
        /*!
            This variable contains the max cooldown in ms
        */
        int _maxCooldownInMS;
    };
}

#endif /* !COOLDOWN_HPP_ */