/*
 * @lc app=leetcode.cn id=11 lang=cpp
 *
 * [11] 盛最多水的容器
 */

// @lc code=start
class Solution
{
public:
    /* Time Limit Exceeded
    int maxArea(vector<int> &height)
    {
        int max_v = 0;
        int size = height.size();
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = size - 1; j > i; j--)
            {
                max_v = std::max(std::min(height[i], height[j]) * (j - i), (size_t)max_v);
            }
        }
        return max_v;
    }*/
    int maxArea(vector<int> &height)
    {
        int max_v = 0;
        int size = height.size();
        int first = 0;
        int end = size - 1;
        while (first < end)
        {
            if (height[first] < height[end])
            {
                max_v = std::max(height[first] * (end - first), max_v);
                first++;
            }
            else
            {
                max_v = std::max(height[end] * (end - first), max_v);
                end--;
            }
        }
        return max_v;
    }
};
// @lc code=end
