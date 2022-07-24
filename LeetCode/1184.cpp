#include <vector>

using namespace std;

class Solution {
public:
    int distanceBetweenBusStops(const vector<int> &distance, int start,
                                int destination) {
        int n = distance.size();
        int a = 0;
        int b = 0;
        int i = start;
        for (; i != destination; i = (i + 1) % n) {
            a += distance[i];
        }
        for (; i != start; i = (i + 1) % n) {
            b += distance[i];
        }
        return min(a, b);
    }
};