#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        sort(arr.begin(), arr.end(), [x](int a, int b){
            if (abs(a - x) == abs(b - x)) {
                return a < b;
            }
            return abs(a - x) < abs(b - x);
        });

        arr.resize(min(k, (int)arr.size()));
        sort(arr.begin(), arr.end());
        return arr;
    }
};