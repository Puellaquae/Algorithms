#include <functional>
#include <iostream>
#include <charconv>
#include <unordered_map>
#include <string>
using namespace std;

class Solution {
    using hash_type = decltype(hash<string>{}(""));
    unordered_map<hash_type, string> m;
public:
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        auto h = hash<string>{}(longUrl);
        m[h] = longUrl;
        char buf[255];
        auto [p, err] = to_chars(buf, buf + 255, h, 36);
        return "https://tiny.url/" + string(buf, p - buf);
    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) { 
        hash_type h;
        from_chars(shortUrl.data() + shortUrl.rfind('/') + 1, shortUrl.data() + shortUrl.size(), h, 36);
        return m[h]; 
    }
};

int main() {
    Solution s;
    cout << s.encode("https://leetcode.com/problems/design-tinyurl") << endl;
    cout << s.decode(s.encode("https://leetcode.com/problems/design-tinyurl")) << endl;
}