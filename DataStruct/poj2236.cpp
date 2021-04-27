// Wireless Network
// Using Union-Find Set
#include <algorithm>
#include <iostream>
#include <vector>

template <class T> struct Node {
    Node* FatherNode;
    T Value;
};

template <class T> Node<T>* Find(Node<T>& node) {
    Node<T>* FatherNode = node.FatherNode;
    if (FatherNode == NULL) {
        return &node;
    }
    if (FatherNode->FatherNode == NULL) {
        return FatherNode;
    }
    for (; FatherNode->FatherNode != NULL; FatherNode = FatherNode->FatherNode)
        ;
    node.FatherNode = FatherNode; // Path Compression
    return FatherNode;
}

template <class T> void Merge(Node<T>& nodeA, Node<T>& nodeB) {
    Find(nodeA)->FatherNode = Find(nodeB);
}

template <class T> bool Same(Node<T>& nodeA, Node<T>& nodeB) { 
    return Find(nodeA)==Find(nodeB);
}

struct Point {
    int x, y;
    bool Available;
};

bool CanConnect(int D, const Point& A, const Point& B) {
    if (A.Available == false || B.Available == false) {
        return false;
    }
    int dx = A.x - B.x;
    int dy = A.y - B.y;
    return (1LL * D * D) >= (1LL * dx * dx + 1LL * dy * dy);
}

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int N, D;
    cin >> N >> D;
    vector<Node<Point> > Coms(N + 1, { NULL, {0, 0, false} });
    for (int i = 1; i <= N; i++) {
        cin >> Coms[i].Value.x >> Coms[i].Value.y;
    }
    char op;
    while (cin >> op) {
        if (op == 'O') {
            int PIndex;
            cin >> PIndex;
            Coms[PIndex].Value.Available = true;
            for (int i = 1; i <= N; i++) {
                if (i == PIndex) {
                    continue;
                }
                if (CanConnect(D, Coms[i].Value, Coms[PIndex].Value)
                    && (!Same(Coms[i], Coms[PIndex]))
                    ) {
                    Merge(Coms[i], Coms[PIndex]);
                }
            }
        }
        else if (op == 'S') {
            int AIndex, BIndex;
            cin >> AIndex >> BIndex;
            if (Same(Coms[AIndex], Coms[BIndex])) {
                cout << "SUCCESS" << endl;
            }
            else {
                cout << "FAIL" << endl;
            }
        }
    }
}