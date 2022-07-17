#include <iostream>
#include <vector>

using namespace std;

class MovingAverage {
    vector<int> win;
    int next_idx = 0;
    int in_win = 0;
    int win_size;
    double last_avg = 0.0;
    double sum = 0.0;
public:
    /** Initialize your data structure here. */
    MovingAverage(int size) {
        win = vector<int>(size, 0);
        win_size = size;
    }
    
    double next(int val) {
        sum -= win[next_idx];
        win[next_idx] = val;
        sum += val;
        next_idx = (next_idx + 1) % win_size;
        in_win = min(in_win + 1, win_size);
        return sum / in_win;
    }
};