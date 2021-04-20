#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// stl
void find_and_replace(std::wstring& src,
                      const std::vector<std::wstring>& sensitive_words)
{
    for (auto& item : sensitive_words)
    {
        std::wstring::size_type pos = 0;
        for (;;)
        {
            pos = src.find(item, pos);
            if (pos != std::wstring::npos)
            {
                src.replace(pos, item.length(), item.length(), '*');
                pos += item.length();
            }
            else
            {
                break;
            }
        }
    }
}

void fpstr(wchar_t* src, size_t src_length, wchar_t* word, size_t word_length)
{
    wchar_t* p = nullptr;
    p = wcsstr(src, word);
    if (p)
    {
        while (p)
        {   
            wmemset(p , '*', word_length);
            p = p + word_length;
            p = wcsstr(p, word);
        }
    }

}

// char*
void find_and_replace_primitive(
    std::wstring& src, const std::vector<std::wstring>& sensitive_words)
{
    for (auto& item : sensitive_words)
    {
        fpstr((wchar_t*)src.c_str(), src.size(), (wchar_t*)item.c_str(),
              item.size());
    }
}

//
void testCase1()
{
    std::wstring src = L"你是一个傻逼，你全家都死了，傻逼儿子，你大爷的";
    std::vector<std::wstring> words;
    words.push_back(L"傻逼");
    words.push_back(L"死");
    //find_and_replace(src, words);
    find_and_replace_primitive(src, words);
    std::wcout << src << std::endl;
}

int main()
{
    testCase1();
    return 0;
}