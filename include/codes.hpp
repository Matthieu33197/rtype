/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** codes
*/

#ifndef CODES_HPP_
	#define CODES_HPP_

namespace Network {

		//! UDP protocol code
		/*!
		 briefThe purpose of this enum is to define the codes used in the network protocol.\n
		 [TCP] = connection and lobby protocol.\n
		 [UDP] = game protocol.\n
		 @param HELLO_TCP [TCP] is used to send the player id to the server
		 @param UDP_PORT [TCP] is used to create a room. args -> (uint16_t)port

		 @param HELLO_UDP [UDP] is used to send the player id to the server
		 @param MOVE [UDP] is used to tel to the server that the user pressed an arrow key and wants to move. args -> player_id vector_x, vector_y
		 @param POS [UDP] is used to send the position of the player to the server. args -> entity_id x, y;entity_id x,y ...
		 @param KILL [UDP] is used to send the id of the player killed to the server. args -> entity_id
		 @param SPAWN [UDP] is used to send the id of the player spawned to the server. args -> entity_type, entity_id, x, y
		*/
	enum Codes {
		HELLO_TCP = 0,
		LOBBY_PORT = 1,
		ID_PLAYER = 2,
		HELLO_LOBBY = 3,
		MOVE = 4,
        UPDATE_ENTITIES = 5,
		SHOOT = 6,
		UNLOAD_ENTITY = 7,
        CREATE_LOBBY = 8,
        JOIN_LOBBY = 9,
        GET_LOBBY_LIST = 10,
		LOBBY_LIST = 11,
        PLAYER_LIST_LOBBY = 12,
        LOBBY_CREATION_SUCCESS = 13,
        LOBBY_CREATION_FAILURE = 14,
		SCORE = 15,
		WAVENBR = 16,
		START_GAME,
		LEAVE,
        POS,
        KILL,
        SPAWN,
		UNKNOWN,
        DISCONNECT,
		INPUT_TCHAT,
		TCHAT,
	};
};

#endif /* !CODES_HPP_ */
