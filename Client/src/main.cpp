/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** main.cpp
*/

#include "../include/client.hpp"

void display_header()
{
    std::cout << "USAGE\t./r-type_client [HOST] [PORT]" << std::endl;
}

bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

int launch(const std::string &host, const std::string &port)
{
    if (!is_digits(port)) {
        std::cerr << "[Error]: port number must be a number" << std::endl;
        return 84;
    }
    Game::Client client(host, static_cast<unsigned short int>(std::atoi(port.c_str())));
    try {
        client.start();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

int main(int ac, char **av)
{
    std::string host;

    if (ac == 2 && !std::string(av[1]).compare("-h") || ac == 1)
        display_header();
    if (ac == 3)
        return launch(std::string(av[1]), std::string(av[2]));
    return 0;
}