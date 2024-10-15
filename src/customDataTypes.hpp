#pragma once

#include <queue>
#include <mutex>
#include <optional>

namespace ThreadSafe
{
    template<typename T>
    class Queue
    {
    private:
        std::mutex queueMux;
        std::queue<T> _queue;
        unsigned int pushLim = UINT_MAX;
    public:
        Queue() = default;

        void Push(const T&& value)
        {
            std::lock_guard<std::mutex> lock(queueMux);
            if (_queue.size() >= pushLim)
                return;
            _queue.push(value);
        }

        void Push(const T& value)
        {
            std::lock_guard<std::mutex> lock(queueMux);
            if (_queue.size() >= pushLim)
                return;
            _queue.push(value);
        }

        std::optional<T> Pop(void)
        {
            std::lock_guard<std::mutex> lock(queueMux);

            if (_queue.empty())
                return {};

            T tempVal = _queue.front();
            _queue.pop();
            return tempVal;
        }

        // Returns queue through move semantics (hopefully)
        // Will swap with empty queue and return the full queue
        // Reduces amount of locks needed
        std::queue<T> GetAll(void)
        {
            std::lock_guard<std::mutex> lock(queueMux);
            std::queue<T> retQueue;
            std::swap( _queue, retQueue);
            return retQueue;
        }

        inline void SetQueueLimit(unsigned int value)
        {
            std::lock_guard<std::mutex> lock(queueMux);
            pushLim = value;
        }

        inline void ClearQueueLimit(void)
        {
            std::lock_guard<std::mutex> lock(queueMux);
            pushLim = UINT_MAX;
        }
    };
}


