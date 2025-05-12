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

    // Helper function to check whether the subtree contains at least one node with value 1
    bool nope(TreeNode* root) {
        if (!root)
            return false;
        if (root->val == 1)
            return true;
        // Recursively check left and right subtrees
        if (nope(root->left))
            return true;
        if (nope(root->right))
            return true;
        return false; // No 1 found in this subtree
    }

    // Main pruning function
    TreeNode* hlo(TreeNode*& root) {
        if (!root)
            return root;

        // Recur for left and right children first (post-order)
        hlo(root->left);
        hlo(root->right);

        // If left subtree has no 1, prune it
        if (!nope(root->left))
            root->left = NULL;

        // If right subtree has no 1, prune it
        if (!nope(root->right))
            root->right = NULL;

        // If current node is 0 and both children are NULL, prune this node too
        if (!root->left && !root->right && root->val != 1)
            return NULL;

        return root; // Keep the current node
    }

    TreeNode* pruneTree(TreeNode* root) {
        return hlo(root); // Start pruning from the root
    }
};
