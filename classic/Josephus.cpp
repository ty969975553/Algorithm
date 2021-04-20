int josephus_recure(int total, int start, int skip)
{
    if (total == 1)
        return start;
    else
        return (josephus_recure(total - 1, start, skip) + skip - start) % total;
}

int josephus_cycle(int total, int start, int skip)
{
    if (total == 1)
        return 0;
    int i = 0;
    int s = start;
    for (i = 2; i <= total; i++)
    {
        s = (s + skip) % i;
    }
    return s;
}
#include <string>
std::string f = "ABCDEFG";

int main()
{
    int surrive1 = josephus_recure(5, 0, 3);
    int surrive2 = josephus_cycle(5, 0, 3);
    return 0;
}