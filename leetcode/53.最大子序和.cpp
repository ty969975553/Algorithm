/*
 * @lc app=leetcode.cn id=53 lang=cpp
 *
 * [53] 最大子序和
 */

// @lc code=start
class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        int max = 0;
        int temp = 0;
        bool all_minus = true;
        int max_minus = 0;

        for (auto &num : nums)
        {
            if (all_minus)
            {
                if (num >= 0)
                {
                    all_minus = false;
                }
                else
                {
                    if (max_minus == 0 || max_minus < num)
                    {
                       max_minus =  num;
                    }
                }
            }

            temp += num;
            if (temp < 0)
            {
                temp = 0;
            }
            if (max < temp)
            {
                max = temp;
            }
            if(all_minus)
            {
                max = max_minus;
            }
        }
        return max;
    }
};
// @lc code=end
