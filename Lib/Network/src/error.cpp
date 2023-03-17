/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** error
*/

#include "../include/error.hpp"

Network::NetworkError::NetworkError(std::string const &message, std::string const &component)
{
	_component = _component;
    _message = message;
}


const char *Network::NetworkError::what() const noexcept
{
    return _message.c_str();
}

std::string const &Network::NetworkError::getComponent() const
{
    return _component;
}

Network::ClientConnectionError::ClientConnectionError(std::string const &message, std::string const &component)
: NetworkError(message, component)
{}