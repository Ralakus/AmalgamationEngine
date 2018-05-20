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

		 ThreadPool() : m_Workers(), m_TaskQueue(), m_TaskCount(0u), m_Mutex(), m_Condition(), m_Stopped(false) {}
		 ThreadPool(std::size_t Threads) : ThreadPool() { InitWithThreads(Threads); }
		~ThreadPool() {
			m_Stopped = true;
			m_Condition.notify_all();
			for (auto& W : m_Workers) {
				W.join();
			}
		}

		void InitWithThreads(std::size_t Threads) {
			for (std::size_t i = 0; i < Threads; i++) {
				m_Workers.emplace_back( [this]() -> void {

					bool Run = true;
					while (Run) {
						std::function<void()> Task;
						{
							std::unique_lock<std::mutex> Lock(m_Mutex);
							m_Condition.wait(Lock, [this]() -> bool {
								return !m_TaskQueue.empty() || m_Stopped;
							});

							if (m_Stopped && m_TaskQueue.empty()) {
								return;
							}

							Task = std::move(m_TaskQueue.front());
							m_TaskQueue.pop();
						}
						Task();
						--m_TaskCount;
					}

				});
			}
		}

		void Schedule(const std::function<void()>& Task) {
			{
				std::unique_lock<std::mutex> Lock(m_Mutex);
				m_TaskQueue.push(Task);
			}
			m_TaskCount++;
			m_Condition.notify_one();
		}

		void WaitAll() const {
			while (m_TaskCount != 0u) {
				std::this_thread::sleep_for( std::chrono::microseconds(1) );
			}
		}
	};

}