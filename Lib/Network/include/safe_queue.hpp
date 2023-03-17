/*
** EPITECH PROJECT, 2023
** B-CPP-500-PAR-5-2-rtype-martin.leblancs
** File description:
** queue
*/

#ifndef SAFE_QUEUE_HPP_
#define SAFE_QUEUE_HPP_

#include <queue>
#include <mutex>
#include <iostream>

namespace Network {

	template <typename MessageType>
	//! SafeQueue class
	/*!
	 The purpose of this class is to create a thread safe queue.
	*/
	class SafeQueue {
		public:
			//! SafeQueue constructor
			SafeQueue() = default;
			//! SafeQueue copy constructor
			/*!
			 * \param to_copy the SafeQueue to copy
			 */
			SafeQueue(const SafeQueue &to_copy)
			{
				_queue = to_copy._queue;
			}
			//! SafeQueue destructor
			~SafeQueue() = default;
			//! push function
			/*!
			 * This function is used to push a message in the queue.
			 * \param msg the message to push
			 */
			void push(const MessageType &msg)
			{
				_queueMutex.lock();
				_queue.push(msg);
				_queueMutex.unlock();
			};
			//! pop function
			/*!
			 * This function is used to pop a message in the queue.
			 */
			void pop()
			{
				_queueMutex.lock();
				_queue.pop();
				_queueMutex.unlock();
			};
			//! front function
			/*!
			 * This function is used to get the first message in the queue.
			 * \return the first message in the queue
			 */
			MessageType &front()
			{
				return _queue.front();
			}
			//! isEmpty function
			/*!
			 * This function is used to check if the queue is empty.
			 * \return true if the queue is empty, false otherwise
			 */
			bool isEmpty() const
			{
				return _queue.empty();
			}

		private:
			std::queue<MessageType> _queue;
			std::mutex _queueMutex;
	};
};

#endif /* !QUEUE_HPP_ */
