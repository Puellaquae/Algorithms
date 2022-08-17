#include <iostream>
#include <map>
#include <vector>

using namespace std;

class OrderedStream {
    map<int, string> m;
    int ptr = 1;

public:
    OrderedStream(int n) {}

    vector<string> insert(int idKey, string value) {
        m[idKey] = value;
        vector<string> ans;
        if (ptr == idKey) {
            ans.push_back(m[ptr]);
            for (ptr++; m.count(ptr) != 0; ptr++) {
                ans.push_back(m[ptr]);
            }
        }
        return ans;
    }
};