/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** error
*/

#ifndef ERROR_HPP_
	#define ERROR_HPP_

	#include <string>
	#include <exception>

namespace Network {
	class NetworkError : public std::exception {
		public:
			NetworkError(std::string const &message, std::string const &component);
			std::string const &getComponent() const;
			const char *what() const noexcept override;
		private:
			std::string _message;
			std::string _component;
	};

	class ClientConnectionError : public NetworkError {
		public:
			ClientConnectionError(std::string const &message, std::string const &component);
	};
}

#endif /* !ERROR_HPP_ */
