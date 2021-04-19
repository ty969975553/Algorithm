// BlockBoundQueue
#include <cstdint>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <cstdio>

namespace base
{
	template <typename T>
	class BlockBoundQueue
	{
	public:
		BlockBoundQueue(std::size_t bound) : bound_(bound) {}
		BlockBoundQueue(const BlockBoundQueue&) = delete;
		BlockBoundQueue& operator=(const BlockBoundQueue&) = delete;
		void push(const T& value)
		{
			std::unique_lock<std::mutex> lck(mutex_);
			while (count_ + 1 == bound_)
			{
				//wait for consumer;
				notFull_.wait(lck);
			}
			count_++;
			queue_.push(value);
			notEmpty_.notify_one();
		}

		void emplace(const T& value)
		{
			std::unique_lock<std::mutex> lck(mutex_);
			while (count_ + 1 == bound_)
			{
				//wait for consumer;
				notFull_.wait(lck);
			}
			count_++;
			queue_.emplace(std::move(value));
			notEmpty_.notify_one();
		}

		void emplace(const T&& value)
		{
			std::unique_lock<std::mutex> lck(mutex_);
			while (count_ + 1 == bound_)
			{
				//wait for consumer;
				notFull_.wait(lck);
			}
			count_++;
			queue_.emplace(value);
			notEmpty_.notify_one();
		}

		T front()
		{
			std::unique_lock<std::mutex> lck(mutex_);
			while (queue_.empty())
			{
				//wait for producer produce
				notEmpty_.wait(lck);
			}
			return queue_.front();
		}

		void pop()
		{
			std::unique_lock<std::mutex> lck(mutex_);
			while (queue_.empty())
			{
				//wait for producer produce
				notEmpty_.wait(lck);
			}
			queue_.pop();
			count_--;
			notFull_.notify_one();
		}

		std::size_t size() { return queue_.size(); }
		// void swap(T &value) { return queue_.swap(value) }

	private:
		std::mutex mutex_;
		std::condition_variable notEmpty_;
		std::condition_variable notFull_;
		std::queue<T> queue_;
		std::size_t count_ = 0;
		std::size_t bound_;
	};
}