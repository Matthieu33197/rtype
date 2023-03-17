/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** shutdown
*/

#ifndef UNLOADID_HPP_
    #define UNLOADID_HPP_

    #include <memory>
    #include <functional>
    #include "../../include/codes.hpp"
    #include "../../Lib/Network/include/server_it.hpp"

	void sendMessageUnloadID(uint32_t id, std::shared_ptr<Network::ServerData<Network::Codes>> &server);

#endif /* !UNLOADID_HPP_ */