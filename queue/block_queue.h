// BlockQueue
#include <cstdint>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <cstdio>

namespace base
{
    template <typename T>
    class BlockQueue
    {
    public:
        BlockQueue() {}
        BlockQueue(const BlockQueue &) = delete;
        BlockQueue &operator=(const BlockQueue &) = delete;
        void push(const T &value)
        {
            std::unique_lock<std::mutex> lck(mutex_);
            queue_.push(value);
            notEmpty_.notify_one();
        }

        void emplace(const T &value)
        {
            std::unique_lock<std::mutex> lck(mutex_);
            queue_.emplace(std::move(value));
            notEmpty_.notify_one();
        }

        void emplace(const T &&value)
        {
            std::unique_lock<std::mutex> lck(mutex_);
            queue_.emplace(value);
            notEmpty_.notify_one();
        }

        T front()
        {
            std::unique_lock<std::mutex> lck(mutex_);
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
        }

        std::size_t size() { return queue_.size(); }

    private:
        std::mutex mutex_;
        std::condition_variable notEmpty_;
        std::queue<T> queue_;
    };
}