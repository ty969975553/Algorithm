/*
 * @lc app=leetcode.cn id=5 lang=cpp
 *
 * [5] 最长回文子串
 */

// @lc code=start
class Solution {
public:
    string longestPalindrome(string s) {
       int max = 0;
		std::string res;
		auto Palindrome = [](int symmetry, string s)->std::string
		{
			int offset = std::min((int)(s.size()-1) * 2 - symmetry, symmetry);
			int long_offset = -1;
			for ( int i = 0; i <= offset; i ++)
			{				
				if (symmetry % 2 != 0)
				{
					if ((symmetry - i -1) % 2 != 0)
					{
						continue;
					}

					if (s.at((symmetry - i - 1) / 2) != s.at((symmetry + i + 1) / 2)) 
					{
						break;
					}
					else 
					{
						long_offset = i;
						continue;
					}
				}
				else
				{
					if ((symmetry - i) % 2 != 0)
					{
						continue;
					}

					if (s.at((symmetry - i) / 2) != s.at((symmetry + i) / 2))
					{
						break;
					}
					else 
					{
						long_offset = i;
						continue;
					}
				}	
			}

			if (symmetry % 2 != 0)
			{
				return (long_offset  == -1) ? "" :
					s.substr((symmetry - long_offset - 1) / 2, long_offset + 2);
			}
			else 
			{
				return s.substr((symmetry - long_offset) / 2, long_offset + 1);
			}
		};
		size_t length = s.size();
		for (size_t i = 0; i <= (length - 1) * 2; i++)
		{
			std::string temp = Palindrome(i, s);
			if (temp.size() > (int)max) {
				res = temp;
				max = temp.size();
			}
		}
		return res;
    }
};
// @lc code=end

