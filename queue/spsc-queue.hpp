// https://github.com/mstump/queues

#ifndef __SPSC_QUEUE_INCLUDED__
#define __SPSC_QUEUE_INCLUDED__

#include <atomic>

template<typename T>
class spsc_queue_t
{
public:

    spsc_queue_t() :
        _head(reinterpret_cast<node_t*>(new node_aligned_t)),
        _tail(_head)
    {
        _head->next = NULL;
    }

    ~spsc_queue_t()
    {
        T output;
        while (this->dequeue(output)) {}
        delete _head;
    }

    void
    enqueue(
        const T& input)
    {
        node_t* node = reinterpret_cast<node_t*>(new node_aligned_t);
        node->data = input;
        node->next = NULL;

        std::atomic_thread_fence(std::memory_order_acq_rel);
        _head->next = node;
        _head = node;
    }

    bool
    dequeue(
        T& output)
    {
        std::atomic_thread_fence(std::memory_order_consume);
        if (!_tail->next) {
            return false;
        }

        output = _tail->next->data;
        std::atomic_thread_fence(std::memory_order_acq_rel);
        _back = _tail;
        _tail = _back->next;

        delete _back;
        return true;
    }


private:

    struct node_t
    {
        node_t* next;
        T       data;
    };

    typedef typename std::aligned_storage<sizeof(node_t), std::alignment_of<node_t>::value>::type node_aligned_t;

    node_t* _head;
    char    _cache_line[64];
    node_t* _tail;
    node_t* _back;

    spsc_queue_t(const spsc_queue_t&) {}
    void operator=(const spsc_queue_t&) {}
};

#endif