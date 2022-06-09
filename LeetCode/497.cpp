#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> rects;
    vector<int> pointCnt;
    random_device r;
    default_random_engine gen{r()};
    uniform_int_distribution<int> dis;

public:
    Solution(vector<vector<int>> &&rects) : rects(rects) {
        pointCnt = vector<int>(rects.size() + 1, 0);
        int pointCntIdx = 1;
        for (vector<int> &rect : rects) {
            int width = rect[2] - rect[0] + 1;
            int height = rect[3] - rect[1] + 1;
            pointCnt[pointCntIdx] = pointCnt[pointCntIdx - 1] + width * height;
            pointCntIdx++;
        }
        dis = uniform_int_distribution<int>(0, pointCnt.back() - 1);
    }

    vector<int> pick() {
        int pos = dis(gen);
        int idx = (upper_bound(pointCnt.begin(), pointCnt.end(), pos) -
                   pointCnt.begin()) -
                  1;
        int posOfRect = pos - pointCnt[idx];
        int xl = rects[idx][0];
        int yl = rects[idx][1];
        int xu = rects[idx][2];
        int yu = rects[idx][3];
        int width = xu - xl + 1;
        int height = yu - yl + 1;
        int x = posOfRect % width;
        int y = posOfRect / width;
        return {xl + x, yl + y};
    }
};

int main() {
    Solution solution({{-2, -2, 1, 1}, {2, 2, 4, 6}});
    for (int i = 0; i < 10; i++) {
        auto pick = solution.pick();
        cout << pick[0] << ";" << pick[1] << endl;
    }
}