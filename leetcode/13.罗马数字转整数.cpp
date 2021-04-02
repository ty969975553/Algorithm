/*
 * @lc app=leetcode.cn id=13 lang=cpp
 *
 * [13] 罗马数字转整数
 */

// @lc code=start
class Solution {
public:
	Solution() 
	{
		
	}
	~Solution() 
	{
		char_map_.clear();
	}
	int romanToInt(string s) {
		int num = 0;
		size_t i = 0; 
		size_t size = s.size();
		while (i < size - 1)
		{
			if (char_map_[s[i]] >= char_map_[s[i + 1]])
			{
				num += char_map_[s[i]];
			}
			else 
			{
				num -= char_map_[s[i]];
			}
			i++;
		}
		return num + char_map_[s[i]];
	}
private:
	map<char, int> char_map_ = { {'I', 1}, {'V', 5},{'X', 10},{'L', 50},{'C', 100},{'D', 500},{'M', 1000}};
};
// @lc code=end

