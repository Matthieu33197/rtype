/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils source file
*/

#include "../../include/utils/utils.hpp"

uint32_t createUuid(void)
{
    std::mt19937 engine(std::random_device{}());
    uint32_t uuid = engine();

    return (uuid);
}