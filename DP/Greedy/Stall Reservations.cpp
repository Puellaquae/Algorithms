#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

struct Compare {
    vector<pair<int, int> > &A;
    Compare(vector<pair<int, int> > &A) : A(A) {}
    bool operator()(int lhs, int rhs) const { return A[lhs].first < A[rhs].first; }
};

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int, int> > Cows(n);
    for (int i = 0; i < n; i++) {
        cin >> Cows[i].first >> Cows[i].second;
    }

    //Map the Index after Sorted into the Index in Origin Order
    vector<int> order(n);
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    //Sort in order by Cow's Left Value, small to big
    sort(order.begin(), order.end(), Compare(Cows));
    
    //The first value in house is RightSide of that Stall,
    //and the second value is the index of that Statll
    multimap<int, int> house;
    
    //The Origin Index of Cow Map to the Index of Stall
    vector<int> assign(n);

    for (int i = 0; i < n; i++) {
        int index = order[i];
        assign[index] = (int)house.size();
        if (!house.empty() && house.begin()->first < Cows[index].first) {
            assign[index] = house.begin()->second;
            house.erase(house.begin());
        }
        house.insert(make_pair(Cows[index].second, assign[index]));
    }


    cout << house.size() << "\n";
    for (int i = 0; i < n; i++) {
        cout << assign[i] + 1 << "\n";
    }
    return 0;
}