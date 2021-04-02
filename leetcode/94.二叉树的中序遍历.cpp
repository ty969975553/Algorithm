/*
 * @lc app=leetcode.cn id=94 lang=cpp
 *
 * [94] 二叉树的中序遍历
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        if(!root)
        {
            return result;
        }
        vector<int> temp;
        if(root->left)
        {
           temp = inorderTraversal(root->left);
           result.insert(result.end(), temp.begin(), temp.end());
        }
        result.emplace_back(root->val);
        if (root->right)
        {
           temp = inorderTraversal(root->right);
           result.insert(result.end(), temp.begin(), temp.end());
        }
        return result;
    }
};
// @lc code=end

