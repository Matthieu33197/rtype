/*
** EPITECH PROJECT, 2018
** R-Type
** File description:
** Timer
*/

#include <chrono>

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

namespace Server {
    class Clock {
        public:
            //! Clock constructor
            /*!
             Default constructor
            */
            Clock() = default;
            //! Clock destructor
            /*!
             Default destructor
            */
            ~Clock() = default;
            //! startClock function
            /*!
             Start the clock
            */
            void startClock();
            //! endClock function
            /*!
             End the clock
            */
            void endClock();
            //! wait function
            /*!
             Wait for the time you want
            */
            void wait();
        private:
            //! _start variable
            /*!
             The start of the clock
            */
            std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::microseconds> _start;
            //! _end variable
            /*!
             The end of the clock
            */
            std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::microseconds> _end;
    };
}

#endif /* !CLOCK_HPP_ */