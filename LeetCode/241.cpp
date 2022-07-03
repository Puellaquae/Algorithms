#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

constexpr int ADD = -1;
constexpr int SUB = -2;
constexpr int MUL = -3;

class Solution {
public:
    void zip(const vector<int> &v1, const vector<int> &v2, int op,
             vector<int> &out) {
        for (int i : v1) {
            for (int j : v2) {
                switch (op) {
                case ADD:
                    out.push_back(i + j);
                    break;
                case SUB:
                    out.push_back(i - j);
                    break;
                case MUL:
                    out.push_back(i * j);
                    break;
                }
            }
        }
    }

    vector<int> calc(map<pair<int, int>, vector<int>> &mem,
                     const vector<int> expr, int begin, int end) {
        if (end - begin == 1 && expr[begin] >= 0) {
            return {expr[begin]};
        }
        if (mem.count(make_pair(begin, end)) != 0) {
            return mem[make_pair(begin, end)];
        }
        vector<int> res;
        for (int i = begin; i < end; i++) {
            if (expr[i] < 0) {
                zip(calc(mem, expr, begin, i), calc(mem, expr, i + 1, end),
                    expr[i], res);
            }
        }
        mem[make_pair(begin, end)] = res;
        return res;
    }
    vector<int> diffWaysToCompute(string expression) {
        stringstream ss(expression);
        vector<int> expr;
        for (;;) {
            int n;
            ss >> n;
            expr.push_back(n);
            char op;
            if (ss >> op) {
                if (op == '+') {
                    expr.push_back(ADD);
                } else if (op == '-') {
                    expr.push_back(SUB);
                } else if (op == '*') {
                    expr.push_back(MUL);
                }
            } else {
                break;
            }
        }
        map<pair<int, int>, vector<int>> mem;
        return calc(mem, expr, 0, expr.size());
    }
};

void test(string expr) {
    for (int v : Solution{}.diffWaysToCompute(expr)) {
        cout << v << ", ";
    }
    cout << endl;
}

int main() {
    test("2-1-1");
    test("2");
    test("0");
    test("2*3-4*5");
}