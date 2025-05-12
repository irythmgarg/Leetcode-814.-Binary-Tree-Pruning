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

    // Function to prune the subtree of nodes that don't contain the value 1
    TreeNode* hlo(TreeNode*& root) {
        if (!root)
            return NULL;

        // Post-order traversal: process left and right children first
        root->left = hlo(root->left);
        root->right = hlo(root->right);

        // If current node is 0 and both subtrees are pruned, prune this node too
        if (root->val != 1 && !root->left && !root->right)
            return NULL;

        return root; // Keep the node if it's 1 or has any child containing 1
    }

    TreeNode* pruneTree(TreeNode* root) {
        return hlo(root);
    }
};
