/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils source file
*/

#include "../../include/utils/sendWaveNumber.hpp"

void sendWaveNumber(uint32_t waveNbr, std::shared_ptr<Network::ServerData<Network::Codes>> &server) {
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::WAVENBR;
    messageUpdate << waveNbr;
    server->notifiyClients(messageUpdate);
}
