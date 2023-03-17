/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
**
*/

#include "../include/Clock.hpp"
#include <thread>

void Server::Clock::startClock()
{
    _start = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
}

void Server::Clock::endClock()
{
    _end = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
}

void Server::Clock::wait()
{
    std::chrono::milliseconds time = std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start);

    if (time.count() < 8000)
        std::this_thread::sleep_for(std::chrono::microseconds(8000 - time.count()));
}