//BlockingReadWriteCircularBuffer
//circular buffer (fixed-size queue).

#include <memory>
namespace base
{
    //single_producer_single_consumer
    namespace spsc 
    {
        template <typename T>
        class BlockingReaderWriterCircularBuffer
        {
        public:
            typedef T value_type;

        public:
            explicit BlockingReaderWriterCircularBuffer(std::size_t capacity)
                : maxcap(capacity), mask(), rawData(), data(),
                  slots(new spsc_sema::LightweightSemaphore(static_cast<spsc_sema::LightweightSemaphore::ssize_t>(capacity))),
                  items(new spsc_sema::LightweightSemaphore(0)),
                  nextSlot(0), nextItem(0)
                  {

                  }
        private:
            std::size_t max_capacity;
        } // namespace spsc
    }
