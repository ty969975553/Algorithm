#include <algorithm>
#include <string>

using string = std::string;
//是否旋转
bool CheckRotation(string s1, string s2)
{
    return s1.size() == s2.size() && (s1 + s1).find(s2) != string::npos;
}

//是否包含所有的字符 大写字母
bool IsContainAllChars(string a, string b)
{
    int64_t hash = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        hash |= (1 << (a[i] - 'A'));
    }

    for (int i = 0; i < b.size(); ++i)
    {
        if ((hash & (1 << (b[i] - 'A'))) == 0)
        {
            return false;
        }
    }

    return true;
}