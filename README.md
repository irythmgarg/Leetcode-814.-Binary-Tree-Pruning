# Leetcode-814.-Binary-Tree-Pruning

Binary Tree Pruning
Problem Statement
Given the root of a binary tree where each node's value is either 0 or 1, the task is to prune the tree such that all subtrees containing only nodes with value 0 (and no nodes with value 1) are removed. A subtree consists of a node and all its descendants. Return the root of the pruned tree.
Tree Node Definition
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

Example
Input: 
      1
     / \
    0   1
   / \
  0   0

Output: 
      1
       \
        1

Explanation: The left subtree rooted at 0 contains only 0s, so it is pruned.
Solution Overview
Two solutions are provided to solve this problem. Both use a recursive approach but differ in their strategy for identifying and pruning subtrees.
Solution 1: Using a Helper Function to Check for 1s
This solution uses a helper function nope to check if a subtree contains at least one node with value 1. The main pruning function hlo performs a post-order traversal, pruning subtrees that lack a 1.
Code
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

How It Works

Helper Function nope:
Recursively checks if a subtree contains a node with value 1.
Returns true if a 1 is found, false otherwise.


Main Function hlo:
Performs a post-order traversal (left, right, root).
Recursively prunes the left and right subtrees.
Uses nope to check if the left or right subtree contains a 1. If not, sets the corresponding child pointer to NULL.
If the current node has value 0 and both children are NULL, the node itself is pruned (returns NULL).
Otherwise, returns the current node.


Edge Cases:
Handles NULL nodes by returning NULL.
Correctly prunes entire trees if they contain no 1s.



Time and Space Complexity

Time Complexity: O(n * h), where n is the number of nodes and h is the height of the tree. For each node, the nope function may traverse the entire subtree (up to height h).
Space Complexity: O(h) for the recursion stack, where h is the height of the tree.

Solution 2: Single-Pass Pruning
This solution prunes the tree in a single pass by checking the validity of subtrees during the post-order traversal, without requiring a separate helper function to check for 1s.
Code
class Solution {
public:
    TreeNode* hlo(TreeNode*& root) {
        if (!root)
            return NULL;
        root->left = hlo(root->left);
        root->right = hlo(root->right);
        if (root->val != 1 && !root->left && !root->right)
            return NULL;
        return root;
    }
    TreeNode* pruneTree(TreeNode* root) {
        return hlo(root);
    }
};

How It Works

Main Function hlo:
Performs a post-order traversal (left, right, root).
Recursively prunes the left and right subtrees, updating the child pointers.
After pruning children, checks if the current node has value 0 and no children (!root->left && !root->right). If so, prunes the node by returning NULL.
Otherwise, returns the current node.


Edge Cases:
Handles NULL nodes by returning NULL.
Correctly prunes entire trees if they contain no 1s.



Time and Space Complexity

Time Complexity: O(n), where n is the number of nodes. Each node is visited exactly once.
Space Complexity: O(h) for the recursion stack, where h is the height of the tree.

Pros and Cons of Each Solution
Solution 1: Using a Helper Function
Pros:

Explicit Logic: The nope function clearly separates the logic for checking the presence of 1s, making the code easier to understand for some readers.
Modular Design: The separation of concerns (checking for 1s vs. pruning) makes it easier to modify the condition for pruning if the problem changes (e.g., pruning based on a different value).

Cons:

Inefficient: The nope function may traverse the same subtree multiple times, leading to a worst-case time complexity of O(n * h).
More Code: Requires additional code for the nope function, increasing the overall length and complexity.
Redundant Traversals: Each node may be visited multiple times (once during pruning and multiple times during nope calls).

Solution 2: Single-Pass Pruning
Pros:

Efficient: Performs a single pass over the tree, resulting in O(n) time complexity.
Concise: Requires less code, making it easier to read and maintain.
No Redundant Traversals: Each node is visited exactly once, and pruning decisions are made immediately.

Cons:

Less Explicit: The logic for checking subtree validity is embedded in the pruning function, which may be less intuitive for some readers.
Less Flexible: Modifying the pruning condition (e.g., to check for a different value) requires changes to the main function, which may be less modular.

Comparison Table



Aspect
Solution 1 (Helper Function)
Solution 2 (Single-Pass)



Time Complexity
O(n * h)
O(n)


Space Complexity
O(h)
O(h)


Code Length
Longer (due to nope function)
Shorter


Readability
More explicit, modular
Concise but less explicit


Efficiency
Less efficient due to multiple traversals
More efficient with single traversal


Flexibility
Easier to modify pruning condition
Less modular, harder to modify


Maintainability
Easier to extend but more code to maintain
Easier to maintain due to simplicity


Which Solution to Choose?

Choose Solution 2 for most cases, as it is more efficient (O(n) vs. O(n * h)) and concise, making it suitable for large trees or performance-critical applications.
Choose Solution 1 if the problem requires frequent modifications to the pruning condition or if code clarity and modularity are prioritized over performance.

Additional Notes

Both solutions correctly handle edge cases, such as an empty tree or a tree with no 1s.
The reference parameter (TreeNode*&) in both solutions is unnecessary since the pointer modifications are handled via assignments to left and right. A regular pointer (TreeNode*) would suffice.
For very unbalanced trees, Solution 1's performance may degrade significantly due to repeated subtree traversals.

