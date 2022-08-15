#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        vector<int> res = arr;
        sort(res.begin(), res.end());
        int num = 0;
        long long sum1 = 0, sum2 = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            sum1 += res[i];
            sum2 += arr[i];
            if (sum1 == sum2) num++;
        }
        return num;
    }
};