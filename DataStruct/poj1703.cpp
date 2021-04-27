// Find them, Catch them
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
    if (FatherNode == NULL) {
        return &node;
    }
    if (FatherNode->FatherNode == NULL) {
        return FatherNode;
    }
    for (; FatherNode->FatherNode != NULL; FatherNode = FatherNode->FatherNode)
        ;
    node.FatherNode = FatherNode;
    return FatherNode;
}
template <class T> void Merge(Node<T> &nodeA, Node<T> &nodeB) {
    Find(nodeA)->FatherNode = Find(nodeB);
}
template <class T> bool Same(Node<T> &nodeA, Node<T> &nodeB) { return Find(nodeA) == Find(nodeB); }

using namespace std;

const int MAX_N = 150000;
int Coms[MAX_N * 2];
int _Find(int A) {
    int Root = A;
    while (Coms[Root] != Root) {
        Root = Coms[Root];
    }
    int i = A;
    while (Coms[i] != Root) {
        int temp = Coms[i];
        Coms[i] = Root;
        i = temp;
    }
    return Root;
}
void _Merge(int A, int B) {
    int RA = _Find(A);
    int RB = _Find(B);
    Coms[RA] = RB;
}

void solve() {
    int N, M;
    scanf("%d%d", &N, &M);
    for (int i = 0; i <= N * 2; i++) {
        Coms[i] = i;
    }
    for (int i = 0; i < M; i++) {
        char op[2];
        int a = 0, b = 0;
        scanf("%s%d%d", op, &a, &b);
        if (op[0] == 'A') {
            if (_Find(a) == _Find(b) || _Find(a + N) == _Find(b + N)) {
                printf("In the same gang.\n");
            } else if (_Find(a) == _Find(b + N) || _Find(a + N) == _Find(b)) {
                printf("In different gangs.\n");
            } else {
                printf("Not sure yet.\n");
            }
        } else if (op[0] == 'D') {
            _Merge(a, b + N);
            _Merge(b, a + N);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
}