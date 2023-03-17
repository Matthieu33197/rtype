/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** connection_type
*/

#ifndef CONNECTION_TYPE_HPP_
	#define CONNECTION_TYPE_HPP_

namespace Network {
	//! ConnectionType enum
	/*!
	 * The purpose of this enum is to know if the connection is a client or a server.
	 @param CLIENT: the connection is a client.
	 @param SERVER: the connection is a server.
	*/
	enum ConnectionType {
		CLIENT = 0,
		SERVER
	};
};

#endif /* !CONNECTION_TYPE_HPP_ */
