/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** vectors
*/

#include "../include/vector.hpp"

std::array<std::tuple<int8_t, int8_t>, 4> mvArray = {
	std::make_tuple(0, -1), // go UP
	std::make_tuple(0, 1), // go DOWN
	std::make_tuple(-1, 0), // go LEFT
	std::make_tuple(1, 0)
};