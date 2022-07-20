#include <unordered_map>
#include <iostream>

using namespace std;

class MyCalendarTwo {
    unordered_map<int, pair<int, int>> tree;
    
public:
    MyCalendarTwo() {}

    void update(int start, int end, int val, int l, int r, int idx) {
        if (r < start || end < l) {
            return;
        }
        if (start <= l && r <= end) {
            tree[idx].first += val;
            tree[idx].second += val;
        } else {
            int mid = (l + r) >> 1;
            update(start, end, val, l, mid, 2 * idx);
            update(start, end, val, mid + 1, r, 2 * idx + 1);
            tree[idx].first = tree[idx].second +
                              max(tree[2 * idx].first, tree[2 * idx + 1].first);
        }
    }

    bool book(int start, int end) {
        update(start, end - 1, 1, 0, 1e9, 1);
        if (tree[1].first > 2) {
            update(start, end - 1, -1, 0, 1e9, 1);
            return false;
        }
        return true;
    }
};