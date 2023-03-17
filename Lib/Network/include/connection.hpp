/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** connection
*/

#ifndef CONNECTION_HPP_
	#define CONNECTION_HPP_

	#include <boost/asio.hpp>
	#include <boost/bind/bind.hpp>
	#include <boost/function.hpp>
	#include <memory>
	#include <string>
	#include <iostream>
	#include "safe_queue.hpp"
	#include "connection_type.hpp"
	#include "message.hpp"
	#include "error.hpp"

namespace Network {
	//! Enum Protocol
	/*!
	 * The purpose of this enum is to know if the connection is a client or a server.
	 @param TCP: the connection is a client.
	 @param UDP: the connection is a server.
	*/
	enum Protocol {
		TCP = 0,
		UDP = 1
	};
	//! Connection class
	/*!
	 * The purpose of this class is to manage the connection to the server and the data exchange
	 */
	template <typename T>
	class Connection : public std::enable_shared_from_this<Connection<T>> {
		public:
			Connection() = default;
			Connection(std::shared_ptr<SafeQueue<OwnedMessage<T>>> &inputQueue)
			: _inputQueue(inputQueue)
			{

			}
			//! Connection constructor
			/*!
			 * \param inputQueue the queue of the messages to send
			 * \param socket the socket of the connection
			 * \param io_context the io_context of the connection
			 */
			Connection(std::shared_ptr<SafeQueue<OwnedMessage<T>>> &inputQueue,
						boost::asio::ip::tcp::socket socket,
						boost::asio::io_context &io_context)
			: _inputQueue(inputQueue), _io_context(io_context),
			 _socketTcp(std::move(socket)), _socketUdp(io_context), _id(0)
			{}
			//! Connection copy constructor
			/*!
			 * \param other the connection to copy
			 */
			Connection(const Connection &) = delete;
			//! Connection destructor
			~Connection() = default;
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
			//! disconnect function
			/*!
			 * This function is used to disconnect the user
			 */
			void disconnect()
			{
				if (_socketTcp.is_open()) {
					boost::asio::post(_io_context,
					[this]() {
						_socketTcp.close();
						_socketUdp.close();
					});
				}
			}
			//! read_header function
			/*!
			 * This function is used to read the header of the message
			 */
			void read_header()
			{
				boost::asio::async_read(_socketTcp,
				boost::asio::buffer(&_tmpMessage.header, sizeof(HeaderMessage<T>)),
				[this](const std::error_code &err, const std::size_t &size) {
					if (!err) {
						if (_tmpMessage.header.size > 0) {
							_tmpMessage.body.resize(_tmpMessage.header.size);
							read_body();
						} else if (_tmpMessage.header.size == 0)
							save_message(Protocol::TCP);
					} else {
						std::cerr << "[ERROR]: Could not read tcp header, id: " << _id << std::endl;
						_socketTcp.close();
						_socketUdp.close();
					}
				});
			}
			//! read_body function
			/*!
			 * This function is used to read the body of the message
			 */
			void read_body()
			{
				boost::asio::async_read(_socketTcp,
				boost::asio::buffer(_tmpMessage.body.data(), _tmpMessage.body.size()),
				[this](const std::error_code &err, const std::size_t &size) {
					if (!err) {
						save_message(Protocol::TCP);
					} else {
						std::cerr << "[ERROR]: Could not read tcp body, id: " << _id << std::endl;
						_socketTcp.close();
						_socketUdp.close();
					}
				});
			}
			//! read_data_header function
			/*!
			 * This function is used to read the header of the data
			 */
			void read_data_header()
			{
				if (_socketTcp.is_open())
					_socketUdp.async_receive_from(boost::asio::buffer(&_tmpData.header, sizeof(HeaderMessage<T>)),
					_remote_endpoint,
					[this](const std::error_code &err, const std::size_t &size) {
					if (!err) {
						if (_tmpData.header.size > 0) {
							_tmpData.body.resize(_tmpData.header.size);
							read_data_body();
						} else if (_tmpData.header.size == 0)
							save_message(Protocol::UDP);
					} else {
						std::cerr << "[ERROR]: Could not read udp header, id: " << _id << std::endl;
						_socketTcp.close();
						_socketUdp.close();
					}
				});
			}
			//! read_data_body function
			/*!
			 * This function is used to read the body of the data
			 */
			void read_data_body()
			{
				_socketUdp.async_receive_from(boost::asio::buffer(_tmpData.body.data(), _tmpData.header.size),
				_remote_endpoint,
				[this](const std::error_code &err, const std::size_t &size) {
					if (!err) {
						save_message(Protocol::UDP);
					} else {
						std::cerr << "[ERROR]: Could not read udp body, id: " << _id << std::endl;
						_socketTcp.close();
						_socketUdp.close();
					}
				});

			}
			//! write_header function
			/*!
			 * This function is used to write the header of the message
			 */
			void write_header()
			{
				boost::asio::async_write(_socketTcp,
				boost::asio::buffer(&_outputCmdQueue.front().header, sizeof(HeaderMessage<T>)),
				[this](std::error_code err, std::size_t size) {
					if (!err) {
						if (_outputCmdQueue.front().header.size > 0)
							write_body();
						else if (_outputCmdQueue.front().header.size == 0) {
							_outputCmdQueue.pop();
							if (!_outputCmdQueue.isEmpty())
								write_header();
						}
					} else
						std::cerr << "[ERROR]: Could not write header, id: " << _id << std::endl;
				});
			}
			//! write_body function
			/*!
			 * This function is used to write the body of the message
			 */
			void write_body()
			{
				boost::asio::async_write(_socketTcp,
				boost::asio::buffer(_outputCmdQueue.front().body.data(), _outputCmdQueue.front().header.size),
				[this](std::error_code err, std::size_t size) {
					if (!err) {
						_outputCmdQueue.pop();
						if (!_outputCmdQueue.isEmpty())
							write_header();
					} else
						std::cerr << "[ERROR]: Could not write body, id: " << _id << std::endl;
				});
			}
			//! write_data_header function
			/*!
			 * This function is used to write the header of the data
			 */
			void write_data_header()
			{
				_socketUdp.async_send_to(boost::asio::buffer(&_outputDataQueue.front().header, sizeof(HeaderMessage<T>)),
				_remote_endpoint,
				[this](std::error_code err, std::size_t size) {
					if (!err) {
						if (_outputDataQueue.front().header.size > 0)
							write_data_body();
						else if (_outputDataQueue.front().header.size == 0) {
							_outputDataQueue.pop();
							if (!_outputDataQueue.isEmpty())
								write_data_header();
						}
					} else
						std::cerr << "[ERROR]: Could not write data header, id: " << _id << std::endl;
				});
			}
			//! write_data_body function
			/*!
			 * This function is used to write the body of the data
			 */
			void write_data_body()
			{
				_socketUdp.async_send_to(boost::asio::buffer(_outputDataQueue.front().body.data(), _outputDataQueue.front().header.size),
				_remote_endpoint,
				[this](std::error_code err, std::size_t size) {
					if (!err) {
						_outputDataQueue.pop();
						if (!_outputDataQueue.isEmpty())
							write_data_header();
					} else
						std::cerr << "[ERROR]: Could not write data body, id: " << _id << std::endl;
				});
			}
			//! send_data function
			/*!
			 * This function is used to send the data
			 * \param data the data to send
			 */
			void send_data(const Message<T> &data)
			{
				if (!_socketUdp.is_open()) {
					std::cerr << "[Error]: udp connection not established" << std::endl;
					return;
				}
				boost::asio::post(_io_context,
				[this, data]() {
					if (_outputDataQueue.isEmpty()) {
						_outputDataQueue.push(data);
						write_data_header();
					} else
						_outputDataQueue.push(data);
				});
			}
			//! save_message function
			/*!
			 * This function is used to save the message
			 * \param type the type of the message
			 */
			void save_message(const Protocol &type)
			{
				OwnedMessage<Connection<T>, T> ownedMessage;

				if (type == Protocol::TCP)
					ownedMessage.msg = _tmpMessage;
				else
					ownedMessage.msg = _tmpData;
				ownedMessage.client = this->shared_from_this();
				_inputQueue->push(ownedMessage);
				if (type == Protocol::TCP)
					read_header();
				else
					read_data_header();
			}
			//! send_message function
			/*!
			 * This function is used to send the message
			 * \param msg the message to send
			 */
			void send_message(const Message<T> &msg)
			{
				if (!_socketTcp.is_open()) {
					std::cerr << "[Error]: tcp connection not established" << std::endl;
					return;
				}
				boost::asio::post(_io_context,
				[this, msg]() {
					if (_outputCmdQueue.isEmpty()) {
						_outputCmdQueue.push(msg);
						write_header();
					} else {
						_outputCmdQueue.push(msg);
					}
				});
			}
			//! connectClient function
			/*!
			 * This function is used to connect the client
			 */
			void connectClient()
			{
				if (_socketTcp.is_open()) {
					std::cout << "read header connectclient" << std::endl;
					read_header();
				}
			}
			//! connectServer function
			/*!
			 * This function is used to connect the server
			 * \param host the host of the server
			 * \param port the port of the server
			 */
			void connectServer(const std::string &host, const unsigned short int &port)
			{
				boost::asio::ip::tcp::resolver resolver(_io_context);
				boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(host, std::to_string(port));

				boost::asio::async_connect(_socketTcp, endpoints,
					[this](std::error_code err, boost::asio::ip::tcp::endpoint endpoint)
					{
						if (!err)
							read_header();
						else {
							throw Network::ClientConnectionError("connection to server failed", "connection");
						}
					});
			}
			//! connectDataStream function
			/*!
			 * This function is used to connect the data stream
			 * \param host the host of the data stream
			 * \param port the port of the data stream
			 */
			void connectDataStream(const std::string &host, const unsigned short int &port)
			{
				boost::system::error_code ec;
				boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(host, ec);

				if (ec.value() != 0) {
					std::cout << "[Error]: " << ec.message() << std::endl;
					return;
				}
				_remote_endpoint = boost::asio::ip::udp::endpoint(ip_address, port);
				_socketUdp.open(boost::asio::ip::udp::v4());
				read_data_header();
			}
			//! openDataStream function
			/*!
			 * This function is used to open the data stream
			 * \param host the host of the data stream
			 * \param port the port of the data stream
			 */
			void openDataStream(const std::string &host, const unsigned short int &port)
			{
				boost::system::error_code ec;
				boost::asio::ip::address ip_address = boost::asio::ip::address::from_string(host, ec);

				if (ec.value() != 0) {
					std::cout << "[Error]: " << ec.message() << std::endl;
					return;
				}
				boost::asio::ip::udp::endpoint endpoint(ip_address, port);
				_socketUdp.open(boost::asio::ip::udp::v4());
				_socketUdp.bind(endpoint);
				read_data_header();
			}
			//! isRemoteConnected function
			/*!
			 * This function check if the remote client already sent a message
			 * that set the _remote_endpoint variable
			 * \return true if _remote_endpoint is set, false otherwise
			 */
			bool isRemoteConnected() const
			{
				if (!_remote_endpoint.address().to_string().compare("0.0.0.0"))
					return false;
				return true;
			}
						//! isConnected()
			/*!
			 * This function if the tcp socket is still open
			 *\return return true if socket is open, false otherwise
			*/
			bool isConnected() const
			{
				return _socketTcp.is_open();
			}
		private:
			SafeQueue<Message<T>> _outputCmdQueue;
			SafeQueue<Message<T>> _outputDataQueue;
			std::shared_ptr<SafeQueue<OwnedMessage<T>>> &_inputQueue;
			boost::asio::ip::tcp::socket _socketTcp;
			boost::asio::ip::udp::socket _socketUdp;
			boost::asio::ip::udp::endpoint _remote_endpoint;
			boost::asio::io_context &_io_context;
			Message<T> _tmpData;
			Message<T> _tmpMessage;
			uint32_t _id;
	};
};

#endif /* !CONNECTION_HPP_ */
