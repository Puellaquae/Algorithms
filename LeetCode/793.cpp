class Solution {
public:
    int preimageSizeFZF(int k) {
        long long p = 5;
        while ((5 * p - 1) / 4 <= k) {
            p *= 5;
        }
        while (k > 0) {
            const int b = (p - 1) / 4;
            if (5 <= k / b) {
                return 0;
            }
            k %= b;
            p /= 5;
        }
        return 5;
    }
};