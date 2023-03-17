/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** client
*/

#ifndef CLIENT_INTERFACE_HPP_
	#define CLIENT_INTERFACE_HPP_

	#include <thread>
	#include <boost/asio.hpp>
	#include <string>
	#include <iostream>
	#include "safe_queue.hpp"
	#include "connection_it.hpp"

namespace Network {
	//! Client class
	/*!
	 * The purpose of this class is to manage the connection to the server and the data exchange
	 */
	template<typename T>
	class Client {
		public:
			Client() = default;
			//! Client constructor
			/*!
			 * \param host the host of the server
			 * \param port the port of the server
			 */
			Client(const std::string &host, const unsigned short int &port)
			: _host(host), _port(port), _serverCmds(std::make_shared<SafeQueue<OwnedMessage<Connection<T>, T>>>()),
			  _connection(std::make_shared<Connection<T>>(_serverCmds, boost::asio::ip::tcp::socket(_io_context), _io_context)),
			  _running(false)
			{}
			//! Client copy constructor
			/*!
			 * \param other the client to copy
			 */
			Client(const Client &) = default;
			//! Client destructor
			~Client()
			{
				//if (_connection->isConnected())
				disconnect();
			}
			//! setId function
			/*!
			 * This function is used to set the id of the connection
			 * \param id the id of the connection
			 */
			void setId(const uint32_t &id)
			{
				_id = id;
			}
			//! getId function
			/*!
			 * This function is used to get the id of the connection
			 * \return the id of the connection
			 */
			uint32_t getId() const
			{
				return _id;
			}
			//! setScore function
			/*!
			 * This function is used to set the score of the connection
			 * \param score the score of the connection
			 */
			void setScore(const uint32_t &score)
			{
				_score = score;
			}
			//! getScore function
			/*!
			 * This function is used to get the score of the connection
			 * \return the score of the connection
			 */
			uint32_t getScore() const
			{
				return _score;
			}
			//! setWaveNbr function
			/*!
			 * This function is used to set the wave number of the connection
			 * \param waveNbr the wave number of the connection
			*/
			void setWaveNbr(const uint32_t &waveNbr)
			{
				_waveNbr = waveNbr;
			}
			//! getWaveNbr function
			/*!
			 * This function is used to get the wave number of the connection
			 * \return the wave number of the connection
			 */
			uint32_t getWaveNbr() const
			{
				return _waveNbr;
			}
			//! connect function
			/*!
			 * This function is used to connect to the server
			 * \return 0 if the connection is successful, -1 otherwise
			*/
			int connect()
			{
				try {
					_connection->connectServer(_host, _port);
					if (!_running) {
						_running = true;
						_ctxThread = std::thread([this]() { _io_context.run(); });
					}
				} catch (std::exception &e) {
					std::cerr << "[Error]: " << e.what() << std::endl;
					return -1;
				}
				return 0;
			}
			//! connectData function
			/*!
			 * This function is used to connect to the server
			 * \param host the host of the server
			 * \param port the port of the server
			 * \return 0 if the connection is successful, -1 otherwise
			 */
			int connectData(const std::string &host, const unsigned short int &port)
			{
				try {
					_connection->connectDataStream(host, port);
					if (!_running) {
						_running = true;
						_ctxThread = std::thread([this]() { _io_context.run(); });
					}
				} catch (std::exception &e) {
					std::cerr << "[Error]: " << e.what() << std::endl;
					return -1;
				}
				return 0;
			}
			//! disconnect function
			/*!
			 * This function is used to disconnect from the server
			 */
			void disconnect()
			{
				if (_connection->isConnected())
					_connection->disconnect();
				_io_context.stop();
				if (_ctxThread.joinable()) {
					_ctxThread.join();
				}
			//	_connection.reset();
			}
			//! send_message function
			/*!
			 * This function is used to send a message to the server
			 * \param msg the message to send
			 */
			void send_message(const Message<T> &msg)
			{
				_connection->sendMessage(msg);
			}
			//! send_data function
			/*!
			 * This function is used to send a message to the server
			 * \param data the message to send
			 */
			void send_data(const Message<T> &data)
			{
				_connection->sendData(data);
			}
			//! get_received_msg function
			/*!
			 * This function is used to get the received messages
			 * \return the received messages
			 */
			std::shared_ptr<SafeQueue<OwnedMessage<Connection<T>, T>>> &get_received_msg()
			{
				return _serverCmds;
			}
		private:
			std::string _host;
			unsigned short int _port;
			std::thread _ctxThread;
			std::shared_ptr<SafeQueue<OwnedMessage<Connection<T>, T>>> _serverCmds;
			boost::asio::io_context _io_context;
			std::shared_ptr<Connection<T>> _connection;
			bool _running;
			uint32_t _id;
			uint32_t _score;
			uint32_t _waveNbr;
	};
};

#endif /* !CLIENT_HPP_ */
