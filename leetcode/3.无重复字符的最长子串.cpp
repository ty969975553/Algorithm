/*
 * @lc app=leetcode.cn id=3 lang=cpp
 *
 * [3] 无重复字符的最长子串
 */

// @lc code=start
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int max = 0;
        string temp;
        for (auto const &c : s) 
        {
            size_t pos = temp.find(c);
            if (pos != string::npos)
            {
                temp = temp.substr(pos + 1, temp.size() - pos - 1);
            }
            temp.push_back(c);
            max = std::max((int)temp.size(), max);
        }
        return max;
    }
};
// @lc code=end

