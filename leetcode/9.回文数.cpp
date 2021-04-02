/*
 * @lc app=leetcode.cn id=9 lang=cpp
 *
 * [9] 回文数
 */

// @lc code=start
class Solution {
public:
    bool isPalindrome(int x) {
        std::string temp = std::to_string(x);
		for (size_t i = 0; i <= (temp.size() / 2); i++) {
			if (temp[i] != temp[temp.size() - i - 1]) 
			{
				return false;
			}
		}
		return true;
    }
};
// @lc code=end

