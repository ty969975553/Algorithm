#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>

namespace base
{
    template <size_t N>
    class bitset
    {
    public:
        bitset() : _bit(N / 8 + 1) {}

        size_t count() { return _count; }

        size_t size() { return N; }

        void set(size_t pos)
        {
            assert(pos < N);
            size_t _byte = pos / 8;
            size_t bit = pos % 8;

            _bit[_byte] |= (1 << bit);
            _count++;
        }

        void reset(size_t pos)
        {
            assert(pos < N);
            size_t _byte = pos / 8;
            size_t bit = pos % 8;

            _bit[_byte] &= (~(1 << bit));
            _count--;
        }

        bool test(size_t pos)
        {
            assert(pos < N);
            size_t _byte = pos / 8;
            size_t bit = pos % 8;

            if (_bit[_byte] &= (1 << bit))
            {
                return true;
            }
            return false;
        }

    private:
        std::vector<char> _bit;
        size_t _count;
    };
}  // namespace base

int main()
{
    std::vector<int> datas = {4, 6, 4, 8, 9, 16, 36, 45};

    base::bitset<50> base_bitset;
    for (auto const &item : datas)
    {
        if (base_bitset.test(item))
        {
            std::cout << item << "exsit" << std::endl;
        }
        else
        {
            base_bitset.set(item);
        }
    }

    for (auto const &item : datas)
    {
        if (std_bitset.test(item))
        {
            std::cout << item << "exsit" << std::endl;
        }
        else
        {
            std_bitset.set(item);
        }
    }
    return 0;
}