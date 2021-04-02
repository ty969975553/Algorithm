/*
 * @lc app=leetcode.cn id=7 lang=cpp
 *
 * [7] 整数反转
 */

// @lc code=start
class Solution {
public:
    int reverse(int x) {
       	double result = 0;
		std::vector<int> nums;
		for (size_t i = 0; ; i++) 
		{
			if (x / 10 != 0) 
			{
				nums.push_back(x % 10);
				x = x / 10;
			}
			else 
			{
				nums.push_back(x);
				break;
			}
		}
		std::reverse(nums.begin(), nums.end());
		for (size_t i = 0; i < nums.size(); i++) 
		{
			result += nums[i] * std::pow(10, i);
		}

		return (result >= std::numeric_limits<int>::min() && result <= std::numeric_limits<int>::max()) ?			
		 static_cast<int>(result) : 0;
    }
};
// @lc code=end

