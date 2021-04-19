#include <iostream>
#include <string>
#include <atomic>
#include <thread>
#include <mutex>
#include <chrono>
#include <assert.h>
#include <vector>

std::vector<int> data;
std::atomic_bool data_ready(false);

// 线程1
void writer_thread()
{
    data.push_back(10); // #1：对data的写操作
    data_ready = true; // #2：对data_ready的写操作
}

// 线程2
void reader_thread()
{
    while (!data_ready.load()) // #3：对data_ready的读操作
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::cout << "data is " << data[0] << "\n"; // #4：对data的读操作
}

struct X
{
    int i;
    std::string s;
};
std::atomic<X *> p;
std::atomic<int> a;
void create_x()
{
    X *x = new X;
    x->i = 42;
    x->s = "hello";
    a.store(99, std::memory_order_relaxed); // 1
    p.store(x, std::memory_order_release);  // 2
}
void use_x()
{
    X *x;
    while (!(x = p.load(std::memory_order_consume))) // 3
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    assert(x->i == 42);                              // 4
    assert(x->s == "hello");                         // 5
    assert(a.load(std::memory_order_relaxed) == 99); // 6
}
int main()
{
    std::thread t1(writer_thread);
    std::thread t2(reader_thread);
    t1.join();
    t2.join();
}