#include <iostream>
#include "queue/SPSCQueue.h"
#include "queue/block_bound_queue.h"
#include "queue/block_queue.h"
#include "queue/spsc-queue.hpp"
#include "queue/spsc-bounded-queue.hpp"
#include "queue/benchmark_function.h"
//#include "queue/readerwritercircularbuffer.h"
#include <thread>
#include <atomic>
#include <functional>
#include <future>

int count = 0;
const int bound_count = 65536;
const int test_count = 100000000;
//const int bound_count = 16;
//const int test_count = 100;
std::atomic<bool> done(false);

void test_rigtorp()
{
	TIMECOUNTBEGIN
		using namespace rigtorp;

	SPSCQueue<int> q(bound_count);
	auto t = std::thread([&] {
		while (!done)
		{
			while (!q.empty())
			{
				q.pop();
			}
		};
		});

	auto t2 = std::thread([&]() {
		for (int i = 0; i < test_count; i++)
		{
			//std::cout<< "producer :" <<i<< std::endl;
			q.push(i);
		}
		done = true;
		});

	t2.join();
	t.join();
	TIMECOUNTEND
}

void testmoodycamel() {}

void testblockboundqueue()
{
	TIMECOUNTBEGIN
		base::BlockBoundQueue<int> bq2(bound_count);
	std::thread t([&]() {
		for (int i = 0; i < test_count; i++)
		{
			bq2.emplace(i);
			//std::cout << "produce " << i << std::endl;
		}
		});

	std::thread t2([&]() {
		for (int i = 0; i < test_count; i++)
		{
			//std::cout << "consumer " << bq2.front() << std::endl;
			bq2.pop();
		}
		});
	t.join();
	t2.join();
	TIMECOUNTEND
}

void testblockqueue()
{
	TIMECOUNTBEGIN
		base::BlockQueue<int> bq2;
	std::thread t([&]() {
		for (int i = 0; i < test_count; i++)
		{
			bq2.emplace(i);
			//std::cout << "produce " << i << std::endl;
		}
		});

	std::thread t2([&]() {
		for (int i = 0; i < test_count; i++)
		{
			//std::cout << "consumer " << bq2.front() << std::endl;
			bq2.pop();
		}
		});
	t.join();
	t2.join();
	TIMECOUNTEND
}

void testspschpp()
{
	TIMECOUNTBEGIN
		spsc_queue_t<int> q;
	std::thread t([&]() {
		size_t count = test_count;
		int value = 0;

		while (count > 0)
		{
			if (q.dequeue(value))
			{
				--count;
			}
		}
		});

	std::thread t2([&]() {
		int value = 0;
		for (int count = 0; count < test_count; ++count) {
			q.enqueue(count);
		}
		});
	t.join();
	t2.join();
	TIMECOUNTEND
}

void testspscboundqueue()
{
	TIMECOUNTBEGIN
	spsc_bounded_queue_t<int> q(bound_count);
	std::thread t([&]() {
		size_t count = test_count;
		int value = 0;

		while (count > 0)
		{
			if (q.dequeue(value))
			{
				//std::cout << "consumer " << value << std::endl;
				--count;
			}
		}
		});

	std::thread t2([&]() {
		int count = test_count;
		while (count > 0) {
			if (q.enqueue(count)) {
				//std::cout << "produce " << count << std::endl;
				--count;
			}
		}
		});
	t.join();
	t2.join();
	TIMECOUNTEND
}

struct MyStruct
{
	int a = 0;
	bool b = true;
};
int main(int argc, char* argv[])
{
	base::BlockBoundQueue<MyStruct> bq2(bound_count);
	MyStruct my1 =  {1,false};
	bq2.emplace(my1);
	bq2.emplace({ 2,false });
	//TIMECOUNTBEGIN
	//test_rigtorp();     //0.578775s
	testblockboundqueue(); //5.55684s
	testblockqueue();  //6.03315s
	//testspschpp(); //13.3675s
	//testspscboundqueue(); //
	//TIMECOUNTEND
	//run_time_statistics(std::bind(test_rigtorp));

	return 0;
}