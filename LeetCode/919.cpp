#include <queue>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class CBTInserter {
    queue<TreeNode*> insertNode; 
    TreeNode* root;

public:
    CBTInserter(TreeNode* root) {
        this->root = root;
        insertNode.push(root);
        while (!insertNode.empty()) {
            auto node = insertNode.front();
            if (node->left != nullptr && node->right != nullptr) {
                insertNode.pop();
                insertNode.push(node->left);
                insertNode.push(node->right);
            } else {
                break;
            }
        }
    }
    
    int insert(int val) {
        auto node = insertNode.front();
        if (node->left == nullptr) {
            node->left = new TreeNode(val);
        } else {
            node->right = new TreeNode(val);
            insertNode.pop();
            insertNode.push(node->left);
            insertNode.push(node->right);
        }
        return node->val;
    }
    
    TreeNode* get_root() {
        return root;
    }
};