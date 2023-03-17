/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** networkAlias
*/

#ifndef NETWORKALIAS_HPP_
	#define NETWORKALIAS_HPP_

	#include "../Lib/Network/include/connection_it.hpp"
	#include "codes.hpp"

	using CombOwnedMsg = Network::OwnedMessage<Network::Connection<Network::Codes>, Network::Codes>;
	using DataOwnedMsg = Network::OwnedMessage<Network::ConnectionUDP<Network::Codes>, Network::Codes>;
	using CommandOwnedMsg = Network::OwnedMessage<Network::ConnectionTCP<Network::Codes>, Network::Codes>;
	using CommandQueue = Network::SafeQueue<Network::OwnedMessage<Network::ConnectionTCP<Network::Codes>, Network::Codes>>;
	using DataQueue = Network::SafeQueue<Network::OwnedMessage<Network::ConnectionUDP<Network::Codes>, Network::Codes>>;
	using CombQueue = Network::SafeQueue<Network::OwnedMessage<Network::Connection<Network::Codes>, Network::Codes>>;

#endif /* !NETWORKALIAS_HPP_ */
