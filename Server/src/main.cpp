/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include <iostream>
#include <stdlib.h>
#include "server_interface.hpp"
#include "../include/ManageLobby.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "You need to pass the port as argument" << std::endl;
        return (84);
    }
    if (atoi(av[1]) == 0) {
        std::cout << "You need to pass a correct port" << std::endl;
        return (84);
    }
    Server::ManageLobby ManageLobby(atoi(av[1]));
    ManageLobby.run();
	return (0);
}
