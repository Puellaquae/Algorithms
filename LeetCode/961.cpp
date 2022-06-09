#include <iostream>
#include <random>
#include <vector>
using namespace std;

int repeatedNTimes(vector<int> nums) {
    int n = nums.size();
    mt19937 gen{random_device{}()};
    uniform_int_distribution<int> dis(0, n - 1);

    while (true) {
        int x = dis(gen), y = dis(gen);
        if (x != y && nums[x] == nums[y]) {
            return nums[x];
        }
    }
}

#define ASSERT(except, actual)                                                 \
    {                                                                          \
        auto res = actual;                                                     \
        if (except != res) {                                                   \
            cout << #actual << "\nexcept: " #except ", but found: " << res     \
                 << "\n";                                                      \
        }                                                                      \
    }

int main() {
    ASSERT(3, repeatedNTimes({1, 2, 3, 3}));
    ASSERT(3, repeatedNTimes({5, 4, 3, 3}));
    ASSERT(2, repeatedNTimes({2, 1, 2, 5, 3, 2}));
    ASSERT(5, repeatedNTimes({5, 1, 5, 2, 5, 3, 5, 4}));
}