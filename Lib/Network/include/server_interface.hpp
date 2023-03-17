///*
//** EPITECH PROJECT, 2023
//** B-CPP-500-PAR-5-2-rtype-martin.leblancs
//** File description:
//** server
//*/

//#ifndef SERVER_INTERFACE_HPP_
//#define SERVER_INTERFACE_HPP_

//#include <string>
//#include <boost/asio.hpp>
//#include <system_error>
//#include <thread>
//#include "safe_queue.hpp"
//#include "connection_it.hpp"
//#include "codes.hpp"


//namespace Network {

//	enum ServerModes {
//		COMMAND = 0,
//		DATA
//	};

//	//! Server class
//	/*!
//	 * The purpose of this class is to manage the connection to the client and the data exchange
//	 */
//	template<typename T>
//	class Server {
//		public:
//			Server() = default;
//			//! Server constructor
//			/*!
//			 * \param host the host of the server
//			 * \param port the port of the server
//			 */
//			Server(const std::string &host, const unsigned short int &port)
//			: _acceptor(_io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
// 			_host(host), _port(port), _dataPort(port), _idCount(0), _clientCmds(std::make_shared<SafeQueue<OwnedMessage<T>>>())
//			{}
//			//! Server copy constructor
//			/*!
//			 * \param other the server to copy
//			 */
//			Server(const Server &cpy) = delete;
//			//! Server destructor
//			~Server()
//			{
//				stop();
//			}
//			//! start function
//			/*!
//			 * This function is used to start the server
//			 * \return 0 if the server is started, -1 otherwise
//			 */
//			int start(const ServerModes &mode)
//			{
//				try {
//					if (mode == ServerModes::COMMAND)
//						waitConnection();
//					else
//						waitDataConnection();
//					_ctxThread = std::thread([this]() { _io_context.run(); });
//				} catch (std::exception &error) {
//					std::cerr << "[ERROR]: " << error.what() << std::endl;
//					return -1;
//				}
//				std::cout << "-- Server runnning on 127.0.0.1:" << _port << " --" << std::endl;
//				return 0;
//			}
//			//! waitConnection function
//			/*!
//			 * This function is used to wait for a client to connect
//			*/
//			void waitConnection()
//			{
//				_acceptor.async_accept([this](std::error_code err, boost::asio::ip::tcp::socket socket) {
//					if (!err) {
//						std::cout << "- Client connected:" << socket.remote_endpoint() << std::endl;
//						std::shared_ptr<ConnectionIT<T>> new_client = std::make_shared<ConnectionTCP<T>>(_clientCmds, std::move(socket), _io_context);
//						_clients.push_back(std::move(new_client));
//						_clients.back()->setId(_idCount);
//						_clients.back()->connectClient();
//						_idCount += 1;
//						waitConnection();
//					} else
//						std::cerr << "[ERROR]: Could not connect, id:" << _idCount << std::endl;
//				});
//			}
//			void waitDataConnection()
//			{
//				std::shared_ptr<Connection<T>> new_client = std::make_shared<Connection<T>>()
//				_clients.push_back(std::move(new_client));
//				_clients.back()->openDataStream(_host, _dataPort);
//			}
//			//! stop function
//			/*!
//			 * This function is used to stop the server
//			 */
//			void stop()
//			{
//				_io_context.stop();
//				if (_ctxThread.joinable())
//					_ctxThread.join();
//				std::cout << "-- Server successfully stopped --" << std::endl;
//			}
//			//! getClientMsg function
//			/*!
//			 * This function is used to get the client message queue
//			 * \return the client message queue
//			 */
//			std::shared_ptr<SafeQueue<OwnedMessage<T>>> &getClientMsg()
//			{
//				return _clientCmds;
//			}
//			//! sendEvent function
//			/*!
//			 * This function is used to send an event to the client
//			 * \param msg the message to send
//			 */
//			//void sendEvent(const Message &msg);
//			//! sendMessage function
//			/*!
//			 * This function is used to send a message to the client
//			 * \param msg the message to send
//			 */
//			void sendMessage(Connection<T> &client, const Message<T> &msg)
//			{
//				client.send_message(msg);
//			}
//			//! send_data function
//			/*!
//			 * This function is used to send data a client
//			 * \param client the client to send the data
//			 * \param msg the message to send
//			 */
//			void send_data(std::shared_ptr<Network::Connection<T>> &client, const Message<T> &msg)
//			{
//				client->send_data(msg);
//			}
//			//! notifiyClients
//			/*!
//			 * This function send through udp protocol a message to every client
//			 * \param msg the message to send
//			*/
//			void notifiyClients(const Message<T> &msg, const std::function<void(const uint32_t &)> &onDisconnect)
//			{
//				uint32_t clientID = 0;

//				for (auto &client : _clients) {
//					if (!client->isConnected()) {
//						clientID = client->getId();
//						std::cout << "[INFO]: client id: " << clientID << " is disconnected" << std::endl;
//						remove_client(clientID);
//						onDisconnect(clientID);
//					}
//					else if (client->isRemoteConnected())
//						client->send_data(msg);
//				}
//			}
//			//! remove_client
//			/*!
//			 * This function remove the client with it's id equal to id parameter
//			 * \param id the id of the client to remove
//			*/
//			void remove_client(const uint32_t &id)
//			{
//				for (int i = 0; i < _clients.size(); i++)
//					if (_clients[i]->getId() == id)
//						_clients.erase(_clients.begin() + i);
//			}
//			//! getDataPort
//			/*!
//			 * This function return the udp port that is going
//			 * to be bind for the next udp connection
//			 * \return udp port
//			*/
//            unsigned short int getDataPort()
//            {
//                return _dataPort;
//            }
//			//! sendMessageUnloadID
//			/*!
//			 * This function sends a message to the client to unload an entity
//			 * \param id entity ID
//			 * \param server the server to send the message from
//			*/
//			void sendMessageUnloadID(uint32_t id, std::shared_ptr<Network::Server<Network::Codes>> &server)
//			{
//				Message<Codes> messageUpdate;
//				std::function<void(const uint32_t &)> empty = [](const uint32_t &) {};

//        		messageUpdate.header.header_id = UNLOAD_ENTITY;
//            	messageUpdate << id;
//        		server->notifiyClients(messageUpdate, empty);
//			}
//		private:
//			unsigned short int _dataPort;
//			unsigned short int _port;
//			std::string _host;
//			std::thread _ctxThread;
//			uint32_t _idCount;
//			boost::asio::io_context _io_context;
//			boost::asio::ip::tcp::acceptor _acceptor;
//			std::shared_ptr<SafeQueue<OwnedMessage<T>>> _clientCmds;
//			std::vector<std::shared_ptr<Network::ConnectionIT<T>>> _clients;
//	};
//};

//#endif /* !SERVER_HPP_ */
