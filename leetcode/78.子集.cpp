/*
 * @lc app=leetcode.cn id=78 lang=cpp
 *
 * [78] 子集
 */

// @lc code=start
class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> r;
        vector<int> vec;
        size_t len = nums.size();
        for(size_t i =0 ; i < (1 << len); ++i)
        {
            for(size_t j = 0; j < len; j++)
            {
                if(i & (1<<j)) vec.push_back(nums[j]);
            }
            r.push_back(vec);
            vec.clear();
        }
        return r;
    }
};
// @lc code=end

