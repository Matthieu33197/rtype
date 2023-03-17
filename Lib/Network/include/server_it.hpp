/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** server_it
*/

#ifndef SERVER_IT_HPP_
	#define SERVER_IT_HPP_

	#include <memory>
	#include <vector>
	#include "safe_queue.hpp"
	#include "message.hpp"
	#include "connection_it.hpp"

namespace Network {
	template<typename T>
	class ServerIT {
		public:
			ServerIT() = default;
			ServerIT(const ServerIT &) = delete;
			//! Server destructor
			//virtual ~ServerIT()
			//{
			//	stop();
			//}
			virtual void remove_client(const uint32_t &id) = 0;
			short int getPort()
			{
				return _port;
			}
			//! start function
			/*!
			 * This function is used to start the server
			 * \return 0 if the server is started, -1 on error
			 */
			int start()
			{
				try {
					waitConnection();
					_ctxThread = std::thread([this]() { _io_context.run(); });
				} catch (std::exception &error) {
					std::cerr << "[ERROR]: " << error.what() << std::endl;
					return -1;
				}
				std::cout << "-- Server runnning on 127.0.0.1:" << _port << " --" << std::endl;
				return 0;
			}
			//! waitConnection function
			/*!
			 * This function is used to wait for a client to connect
			 */
			virtual void waitConnection()
			{}
			//! stop function
			/*!
			 * This function is used to stop the server
			 */
			//void stop()
			//{
			//	_io_context.stop();
			//	if (_ctxThread.joinable())
			//		_ctxThread.join();
			//	std::cout << "-- Server successfully stopped --" << std::endl;
			//}
		protected:
			std::string _host;
			unsigned short int _port;
			unsigned short int _maxClient;
			boost::asio::io_context _io_context;
			std::thread _ctxThread;
	};

	template<typename T>
	class ServerData : public ServerIT<T> {
		public:
			ServerData(const std::string &host,
					   const unsigned short int &port,
					   const unsigned short int &maxClient = 4)
			: _clientCmds(std::make_shared<SafeQueue<OwnedMessage<ConnectionUDP<T>, T>>>())
			{
				this->_host = host;
				this->_port = port;
				this->_maxClient = maxClient;
				this->_server = std::make_shared<Network::ConnectionUDP<T>>(_clientCmds, this->_io_context);
			}
			~ServerData()
			{
				stop();
			}
			void stop()
			{
				this->_io_context.stop();
				if (this->_ctxThread.joinable())
					this->_ctxThread.join();
				std::cout << "-- Data server successfully stopped --" << std::endl;
			}
			ServerData(const ServerData &) = delete;
			//! waitConnection function
			/*!
			 * This function is used to wait for a client to connect
			 */
			void waitConnection() override
			{
				_server->openDataStream(this->_host, this->_port);
			}
			//! send function
			/*!
			 * This function is used to send data a client
			 * \param client the client to send the data
			 * \param msg the message to send
			 */
			void send(std::shared_ptr<ConnectionUDP<T>> &client, const Message<T> &msg)
			{
				client->sendData(msg);
			}

			void append_client(std::shared_ptr<ConnectionUDP<T>> client)
			{
				_clients.push_back(std::move(client));
			}

			void notifiyClients(const Message<T> &msg)
			{
				for (auto &client : _clients)
					if (client->isRemoteConnected())
						client->sendData(msg);
			}
			//! remove_client
			/*!
			 * This function remove the client with it's id equal to id parameter
			 * \param id the id of the client to remove
			*/
			void remove_client(const uint32_t &id)
			{
				for (int i = 0; i < _clients.size(); i++)
					if (_clients[i]->getId() == id)
						_clients.erase(_clients.begin() + i);
			}

			//! getClientMsg function
			/*!
			 * This function is used to get the client message queue
			 * \return the client message queue
			 */
			std::shared_ptr<Network::SafeQueue<Network::OwnedMessage<Network::ConnectionUDP<T>, T>>> &getClientMsg()
			{
				return _clientCmds;
			}

		private:
			std::shared_ptr<Network::ConnectionUDP<T>> _server;
			std::vector<std::shared_ptr<Network::ConnectionUDP<T>>> _clients;
			std::shared_ptr<Network::SafeQueue<Network::OwnedMessage<Network::ConnectionUDP<T>, T>>> _clientCmds;
	};

	template<typename T>
	class ServerCommand : public ServerIT<T> {
		public:
			ServerCommand(const std::string &host, const unsigned short int &port, const unsigned short int &maxClient = 4)
			: _acceptor(this->_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
			{
				this->_host = host;
				this->_port = port;
				this->_clientCmds = std::make_shared<Network::SafeQueue<Network::OwnedMessage<Network::ConnectionTCP<T>, T>>>();
			}
			~ServerCommand()
			{
				stop();
			}
			void stop()
			{
				this->_io_context.stop();
				if (this->_ctxThread.joinable())
					this->_ctxThread.join();
				std::cout << "-- Command server successfully stopped --" << std::endl;
			}
			ServerCommand(const ServerCommand &) = delete;
			//! waitConnection function
			/*!
			 * This function is used to wait for a client to connect
			 */
			void waitConnection() override
			{
				_acceptor.async_accept([this](std::error_code err, boost::asio::ip::tcp::socket socket) {
					if (!err) {
						std::cout << "- Client connected:" << socket.remote_endpoint() << std::endl;
						std::shared_ptr<ConnectionTCP<T>> new_client = std::make_shared<ConnectionTCP<T>>(this->_clientCmds, std::move(socket), this->_io_context);
						_clients.push_back(std::move(new_client));
						_clients.back()->connectClient();
						waitConnection();
					} else
						std::cerr << "[ERROR]: Could not connect to tcp client" << std::endl;
				});
			}

			//! send function
			/*!
			 * This function is used to send message to a client
			 * \param client the client to send the data
			 * \param msg the message to send
			 */
			void send(std::shared_ptr<ConnectionTCP<T>> &client, const Message<T> &msg)
			{
				client->sendMessage(msg);
			}
			//! remove_client
			/*!
			 * This function remove the client with it's id equal to id parameter
			 * \param id the id of the client to remove
			*/
			void remove_client(const uint32_t &id)
			{
				for (int i = 0; i < _clients.size(); i++)
					if (_clients[i]->getId() == id) {
						_clients.erase(_clients.begin() + i);
					}
			}
			void notifiyClients(const Message<T> &msg, const std::function<void(const uint32_t &)> &handler)
			{
				for (auto &client : _clients) {
					if (client->isConnected())
						client->sendMessage(msg);
				}
			}

			//! getClientMsg function
			/*!
			 * This function is used to get the client message queue
			 * \return the client message queue
			 */
			std::shared_ptr<Network::SafeQueue<Network::OwnedMessage<Network::ConnectionTCP<T>, T>>> &getClientMsg()
			{
				return _clientCmds;
			}

		private:
			boost::asio::ip::tcp::acceptor _acceptor;
			std::vector<std::shared_ptr<Network::ConnectionTCP<T>>> _clients;
			std::shared_ptr<Network::SafeQueue<Network::OwnedMessage<Network::ConnectionTCP<T>, T>>> _clientCmds;
	};

}


#endif /* !SERVER_IT_HPP_ */
