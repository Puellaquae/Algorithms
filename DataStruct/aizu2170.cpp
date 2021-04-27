// Marked Ancestor
// Using Union-Find Set
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

template <class T> struct Node {
    Node *FatherNode;
    T Value;
};

template <class T> Node<T> *Find(Node<T> &node) {
    Node<T> *FatherNode = node.FatherNode;
    if (FatherNode->FatherNode == NULL) {
        return FatherNode;
    }
    for (; FatherNode->FatherNode != NULL; FatherNode = FatherNode->FatherNode)
        ;
    return FatherNode;
}

// Set A's Father Node Equal To B's root
template <class T> void Merge(Node<T> &nodeA, Node<T> &nodeB) {
    Find(nodeA)->FatherNode = Find(nodeB);
}

template <class T> bool Same(Node<T> &nodeA, Node<T> &nodeB) { return Find(nodeA) == Find(nodeB); }

template <class T> bool Isolated(Node<T> &node) { return Find(node) == &node; }

struct P {
    int Index;
    bool Marked;
};

using namespace std;
int main() {
    int N, Q;
    while (cin >> N >> Q && N && Q) {
        vector<Node<P> > Nodes(N, {NULL, {0, false}});
        Nodes[0].Value.Marked = true;
        for (int i = 1; i < N; i++) {
            int F;
            cin >> F;
            Nodes[i].Value.Index = i;
            Nodes[i].FatherNode = &Nodes[F];
        }
        long long ans = 0;
        for (int i = 0; i < Q; i++) {
            char Op;
            int Index;
            cin >> Op >> Index;
            if (Op == 'M') {
                Nodes[Index].Value.Marked = true;
            } else {
                Node<P> *node = &Nodes[Index];
                for (; node->FatherNode != NULL; node = node->FatherNode) {
                    if (node->Value.Marked) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}