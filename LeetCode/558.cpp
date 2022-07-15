#include <iostream>

using namespace std;

class Node {
public:
    bool val;
    bool isLeaf;
    Node *topLeft;
    Node *topRight;
    Node *bottomLeft;
    Node *bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight,
         Node *_bottomLeft, Node *_bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
public:
    Node *intersect(Node *quadTree1, Node *quadTree2) {
        Node *ans = new Node();
        if (!quadTree1->isLeaf && !quadTree2->isLeaf) {
            ans->isLeaf = false;
            ans->topLeft = intersect(quadTree1->topLeft, quadTree2->topLeft);
            ans->topRight = intersect(quadTree1->topRight, quadTree2->topRight);
            ans->bottomLeft =
                intersect(quadTree1->bottomLeft, quadTree2->bottomLeft);
            ans->bottomRight =
                intersect(quadTree1->bottomRight, quadTree2->bottomRight);
            bool allLeaf = ans->bottomLeft->isLeaf &&
                           ans->bottomRight->isLeaf && ans->topLeft->isLeaf &&
                           ans->topRight->isLeaf;
            bool mergeT = ans->bottomLeft->val && ans->bottomRight->val &&
                          ans->topLeft->val && ans->topRight->val;
            bool mergeF = ans->bottomLeft->val || ans->bottomRight->val ||
                          ans->topLeft->val || ans->topRight->val;
            if (allLeaf && (mergeT || !mergeF)) {
                ans = new Node();
                ans->isLeaf = true;
                ans->val = mergeT | mergeF;
            }
        } else if (quadTree1->isLeaf && quadTree2->isLeaf) {
            ans->isLeaf = true;
            ans->val = quadTree1->val || quadTree2->val;
        } else {
            Node *leaf = quadTree1->isLeaf ? quadTree1 : quadTree2;
            Node *branch = quadTree1->isLeaf ? quadTree2 : quadTree1;
            if (leaf->val) {
                ans->isLeaf = true;
                ans->val = true;
            } else {
                ans = branch;
            }
        }
        return ans;
    }
};