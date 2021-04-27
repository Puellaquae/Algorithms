// Structure of Binary Search Tree
#include <iostream>
#include <string>
#include <vector>

template <class T> class BST {
public:
    BST *FatherNode = NULL;
    BST *LeftNode = NULL;
    BST *RightNode = NULL;
    T Value;
    int Rank = 0;
    BST *Find(T Val) {
        if (Rank == 0) {
            return NULL;
        }
        if (Value == Val) {
            return this;
        } else if (Value < Val) {
            if (this->RightNode != NULL)
                return this->RightNode->Find(Val);
            else
                return NULL;
        } else {
            if (this->LeftNode != NULL)
                return this->LeftNode->Find(Val);
            else
                return NULL;
        }
    }
    BST *Root() {
        BST *Node = this;
        while (Node->FatherNode != NULL) {
            Node = Node->FatherNode;
        }
        return Node;
    }
    BST *Insert(T Val) {
        if (Rank == 0) {
            Value = Val;
            Rank = 1;
            return this;
        }
        if (Value == Val) {
            return this;
        } else if (Value < Val) {
            if (this->RightNode != NULL)
                return this->RightNode->Insert(Val);
            else {
                BST *X = new BST;
                X->Value = Val;
                X->Rank = Rank + 1;
                X->FatherNode = this;
                this->RightNode = X;
                return X;
            }
        } else {
            if (this->LeftNode != NULL)
                return this->LeftNode->Insert(Val);
            else {
                BST *X = new BST;
                X->Value = Val;
                X->Rank = Rank + 1;
                X->FatherNode = this;
                this->LeftNode = X;
                return X;
            }
        }
    }
};

void toInt(std::string &cmd, int &valA, int &valB) {
    bool flag = false;
    valA = valB = 0;
    int i = 0;
    if (cmd[i] == '-') {
        i++;
        flag = true;
    }
    while ('0' <= cmd[i] && cmd[i] <= '9') {
        valA = valA * 10 + cmd[i] - '0';
        i++;
    }
    if (flag)
        valA = -valA;
    flag = false;
    for (; i < (int)cmd.size() && !(cmd[i] == '-' || ('0' <= cmd[i] && cmd[i] <= '9')); i++)
        ;
    if (i == cmd.size()) {
        return;
    }
    if (cmd[i] == '-') {
        i++;
        flag = true;
    }
    while ('0' <= cmd[i] && cmd[i] <= '9') {
        valB = valB * 10 + cmd[i] - '0';
        i++;
    }
    if (flag)
        valB = -valB;
}

const char OP_Root = 'T';
const char OP_Siblings = 'B';
const char OP_SameLevel = 'S';
const char OP_Left = 'L';
const char OP_Right = 'R';
const char OP_Parent = 'F';

void Parse(char &op, int &valA, int &valB) {
    std::string cmd;
    std::getline(std::cin, cmd);
    if (cmd.back() == 't') {
        op = OP_Root;
    } else if (cmd.back() == 's') {
        op = OP_Siblings;
    } else if (cmd.back() == 'l') {
        op = OP_SameLevel;
    } else if (cmd.find("parent") != std::string::npos) {
        op = OP_Parent;
    } else if (cmd.find("left") != std::string::npos) {
        op = OP_Left;
    } else if (cmd.find("right") != std::string::npos) {
        op = OP_Right;
    }
    toInt(cmd, valA, valB);
    //std::cout << op << " " << valA << " " << valB << std::endl;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cout.tie(NULL);
    std::cin.tie(NULL);
    BST<int> X;
    int t;
    std::cin >> t;
    while (t--) {
        int v;
        std::cin >> v;
        X.Insert(v);
    }
    std::cin >> t;
    std::string clearcin;
    std::getline(std::cin, clearcin);
    while (t--) {
        char op;
        int valA, valB;
        Parse(op, valA, valB);
        if (op == OP_Root) {
            if (X.Rank == 1 && X.Value == valA) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else if (op == OP_Siblings) {
            BST<int> *A = X.Find(valA);
            BST<int> *B = X.Find(valB);
            if (A != NULL && B != NULL && A != B && A->FatherNode == B->FatherNode) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else if (op == OP_Parent) {
            BST<int> *A = X.Find(valA);
            BST<int> *B = X.Find(valB);
            if (A != NULL && B != NULL && B != A && B->FatherNode == A) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else if (op == OP_Left) {
            BST<int> *A = X.Find(valA);
            BST<int> *B = X.Find(valB);
            if (A != NULL && B != NULL && B != A && B->LeftNode == A) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else if (op == OP_Right) {
            BST<int> *A = X.Find(valA);
            BST<int> *B = X.Find(valB);
            if (A != NULL && B != NULL && B != A && B->RightNode == A) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        } else if (op == OP_SameLevel) {
            BST<int> *A = X.Find(valA);
            BST<int> *B = X.Find(valB);
            if (A != NULL && B != NULL && A->Rank == B->Rank) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }
    return 0;
}