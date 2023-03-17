/*
** EPITECH PROJECT, 2023
** R-Type
** File description:
** ManageClients header file
*/

#ifndef MANAGECLIENTS_HPP_
#define MANAGECLIENTS_HPP_

#include "Lobby.hpp"
#include "../../include/NetworkAlias.hpp"
#include "../../Lib/Network/include/server_it.hpp"
#include "thread_codes.hpp"
#include <memory>
#include <unordered_map>

namespace Server {
    class ManageLobby {
        public:
            //!  ManageLobby constructor
            /*!
             The constructor of the ManageLobby class
             @param port The port of the server
             */
            ManageLobby(const unsigned short int &port);
            //!  ManageLobby destructor
            /*!
             The destructor of the ManageLobby class
             */
            ManageLobby() = default;
            //! getMessages function
            /*!
             Get the messages from the clients
             */
            void getMessages();
            //! manageLobby function
            /*!
             Manage the lobby
             */
            void manageLobby();
            //! run function
            /*!
             Run the server
             */
            void run();
        private:
            //! readProcessMessages function
            /*!
             Read the messages from the processMsg queue
             */
			void readProcessMessages();
            //! updateLobbyList function
            /*!
             Update the lobby list
             */
			void updateLobbyList();
            //! sendChatMessage function
            /*!
             Send the chat message to the clients
             @param owner The owner of the message
             */
            void sendChatMessage(CommandOwnedMsg owner);
            //! _port variable
            /*!
             The port of the server
             */
            unsigned short int _port;
            //! _lobbyPort variable
            /*!
             The port of the lobby
             */
			unsigned short int _lobbyPort;
            //! _listLobby variable
            /*!
             The list of the lobby
             */
            std::unordered_map<uint32_t, std::unique_ptr<Server::Lobby>> _listLobby;
            //! _server variable
            /*!
             The server
             */
            std::shared_ptr<Network::ServerCommand<Network::Codes>> _server;
            //! _msgList variable
            /*!
             The list of the messages
             */
            std::shared_ptr<CommandQueue> _msgList;
            //! _processMsg variable
            /*!
             The queue of the messages to process
             */
			std::shared_ptr<Network::SafeQueue<Network::Message<Thread::codes>>> _processMsg;
            //! _chatMessage variable
            /*!
             The chat message
             */
            std::string _chatMessage;
    };
}

#endif //MANAGECLIENTS_HPP_
