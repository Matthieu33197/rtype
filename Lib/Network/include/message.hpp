/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** Message
*/

#ifndef MESSAGE_HPP_
	#define MESSAGE_HPP_

	#include <cstdint>
	#include <vector>
	#include <memory>
	#include <cstring>

namespace Network {
	//! HeaderMessage struct
	/*!
	 * The purpose of this struct is to define the header of the message.
	 * @param header_id: the id of the header.
	 * @param size: the size of the message.
	*/

	enum Protocol {
		TCP = 0,
		UDP = 1
	};

	template <typename T>
	struct HeaderMessage {
		T header_id;
		uint32_t size = 0;
	};
	//! Message struct
	/*!
	 * The purpose of this struct is to define the message.
	 * @param header: the header of the message.
	 * @param body: the body of the message.
	*/

	template <typename T>
	struct Message {
		HeaderMessage<T> header;
		std::vector<uint8_t> body;
		template<typename DataType>
		//! This function is used to add data to the message. operator<<
		/*!
		 @param msg: the message to add data to.
		 @param data: the data to add to the message.
		 @return the message with the data added.
		 @example: msg << 1 << 2 << 3;
		 @example: msg << "Hello World";
		 @example: msg << std::vector<int>{1, 2, 3};
		*/
		friend Message &operator<<(Message<T> &msg, const DataType &data) {
			size_t i;

			static_assert(std::is_standard_layout<DataType>::value, "Data is not a standard type");
			i = msg.body.size();
			msg.body.resize(i + sizeof(DataType));
			msg.header.size = msg.body.size();
			std::memcpy(msg.body.data() + i, &data, sizeof(DataType));
			return msg;
		}

		template<typename DataType>
		//! This function is used to extract data from the message. operator>>
		/*!
		 @param msg: the message to extract data from.
		 @param data: the data to extract from the message.
		 @return the message with the data extracted.
		 @example: msg >> 1 >> 2 >> 3;
		 @example: msg >> "Hello World";
		 @example: msg >> std::vector<int>{1, 2, 3};
		*/
		friend Message &operator>>(Message<T> &msg, DataType& data)
		{
			size_t i;
			static_assert(std::is_standard_layout<DataType>::value, "Data is not a standard type");

			i = msg.body.size() - sizeof(DataType);
			std::memcpy(&data, msg.body.data() + i, sizeof(DataType));
			msg.body.resize(i);
			msg.header.size = msg.body.size();
			return msg;
		}
	};

	template <typename T>
	class ConnectionIT;
	//! OwnedMessage struct
	/*!
	 * The purpose of this struct is to define the message with the client.
	 * @param client: the client of the message.
	 * @param msg: the message.
	*/
	template <typename U, typename T>
	struct OwnedMessage {
		std::shared_ptr<U> client;
		Message<T> msg;
	};
};

#endif /* !MESSAGE_HPP_ */
