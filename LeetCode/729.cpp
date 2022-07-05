#include <iostream>
#include <set>
#include <vector>

using namespace std;

class MyCalendar {
    set<pair<int, int>> ts;

public:
    MyCalendar() { }

    bool book(int start, int end) {
        auto t = ts.lower_bound(make_pair(end, 0));
        if (t == ts.begin() || (--t)->second <= start) {
            ts.insert(make_pair(start, end));
            return true;
        } else {
            return false;
        }
    }
};

void test(const vector<pair<int, int>> &t) {
    MyCalendar c;
    for (auto &p : t) {
        cout << c.book(p.first, p.second) << endl;
    }
}

int main() {
    test({{47, 50},
          {33, 41},
          {39, 45},
          {33, 42},
          {25, 32},
          {26, 35},
          {19, 25},
          {3, 8},
          {8, 13},
          {18, 27}});
}