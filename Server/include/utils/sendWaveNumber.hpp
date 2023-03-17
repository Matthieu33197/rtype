/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** shutdown
*/

#ifndef SENDWAVENUMBER_HPP_
    #define SENDWAVENUMBER_HPP_

    #include <memory>
    #include <functional>
    #include "../../include/codes.hpp"
    #include "../../Lib/Network/include/server_it.hpp"

	void sendWaveNumber(uint32_t waveNbr, std::shared_ptr<Network::ServerData<Network::Codes>> &server);

#endif /* !SENDWAVENUMBER_HPP_ */