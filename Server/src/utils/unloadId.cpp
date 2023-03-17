/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** utils source file
*/

#include "../../include/utils/unloadId.hpp"

void sendMessageUnloadID(uint32_t id, std::shared_ptr<Network::ServerData<Network::Codes>> &server) {
    Network::Message<Network::Codes> messageUpdate;
    messageUpdate.header.header_id = Network::UNLOAD_ENTITY;
    messageUpdate << id;
    server->notifiyClients(messageUpdate);
}