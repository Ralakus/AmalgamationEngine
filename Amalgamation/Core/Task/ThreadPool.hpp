#pragma once

#include "../Types/Singleton.hpp"

#include <thread>
#include <mutex>
#include <atomic>
#include <functional>
#include <condition_variable>
#include <vector>
#include <queue>

namespace Amalgamation {

	class ThreadPool {

		std::vector<std::thread>          m_Workers;
		std::queue<std::function<void()>> m_TaskQueue;
		std::atomic_uint                  m_TaskCount;
		std::mutex                        m_Mutex;
		std::condition_variable           m_Condition;
		std::atomic_bool                  m_Stopped;

	public:

		ThreadPool();
		ThreadPool(std::size_t Threads);
		~ThreadPool();

		void InitWithThreads(std::size_t Threads);

		void Schedule(const std::function<void()>& Task);

		void WaitAll() const;
	};

}

#include "ThreadPool.inl"