// Detect the Virus

//
//  base64 encoding and decoding with C++.
//  Version: 2.rc.04 (release candidate)
//

#include <cstring>
#include <stdexcept>

/*
   base64.cpp and base64.h
   base64 encoding and decoding with C++.
   More information at
     https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
   Version: 2.rc.04 (release candidate)
   Copyright (C) 2004-2017, 2020 René Nyffenegger
   This source code is provided 'as-is', without any express or implied
   warranty. In no event will the author be held liable for any damages
   arising from the use of this software.
   Permission is granted to anyone to use this software for any purpose,
   including commercial applications, and to alter it and redistribute it
   freely, subject to the following restrictions:
   1. The origin of this source code must not be misrepresented; you must not
      claim that you wrote the original source code. If you use this source code
      in a product, an acknowledgment in the product documentation would be
      appreciated but is not required.
   2. Altered source versions must be plainly marked as such, and must not be
      misrepresented as being the original source code.
   3. This notice may not be removed or altered from any source distribution.
   René Nyffenegger rene.nyffenegger@adp-gmbh.ch
*/

unsigned int pos_of_char(const unsigned char chr) {
    //
    // Return the position of chr within base64_encode()
    //

    if (chr >= 'A' && chr <= 'Z')
        return chr - 'A';
    if (chr >= 'a' && chr <= 'z')
        return chr - 'a' + ('Z' - 'A') + 1;
    if (chr >= '0' && chr <= '9')
        return chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
    if (chr == '+' || chr == '-')
        return 62;
    // Be liberal with input and accept both url ('-') and non-url ('+') base 64 characters (
    if (chr == '/' || chr == '_')
        return 63;
    // Ditto for '/' and '_'

    throw std::runtime_error("If input is correct, this line should never be reached.");
}

#include <string>

std::string decode(const std::string &encoded_string) {
    //
    // decode(…) is templated so that it can be used with String = const std::string&
    // or std::string_view (requires at least C++17)
    //

    size_t length_of_string = encoded_string.length();
    if (!length_of_string)
        return std::string("");

    size_t in_len = length_of_string;
    size_t pos = 0;

    //
    // The approximate length (bytes) of the decoded string might be one ore
    // two bytes smaller, depending on the amount of trailing equal signs
    // in the encoded string. This approximation is needed to reserve
    // enough space in the string to be returned.
    //
    size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
    std::string ret;
    ret.reserve(approx_length_of_decoded_string);

    while (pos < in_len) {

        unsigned int pos_of_char_1 = pos_of_char(encoded_string[pos + 1]);

        ret.push_back(
                static_cast<std::string::value_type>(((pos_of_char(encoded_string[pos + 0])) << 2) +
                    ((pos_of_char_1 & 0x30) >> 4)));

        if (encoded_string[pos + 2] != '=' && encoded_string[pos + 2] != '.') {
            // accept URL-safe base 64 strings, too, so check for '.' also.

            unsigned int pos_of_char_2 = pos_of_char(encoded_string[pos + 2]);
            ret.push_back(
                    static_cast<std::string::value_type>(((pos_of_char_1 & 0x0f) << 4) + ((
                        pos_of_char_2 & 0x3c) >> 2)));

            if (encoded_string[pos + 3] != '=' && encoded_string[pos + 3] != '.') {
                ret.push_back(
                        static_cast<std::string::value_type>(((pos_of_char_2 & 0x03) << 6) +
                            pos_of_char(encoded_string[pos + 3])));
            }
        }

        pos += 4;
    }

    return ret;
}

#include <vector>

template <class T>
std::vector<T> decode(const std::string &encoded_string) {
    //
    // decode(…) is templated so that it can be used with String = const std::string&
    // or std::string_view (requires at least C++17)
    //

    size_t length_of_string = encoded_string.length();
    if (!length_of_string)
        return std::vector<T>();

    size_t in_len = length_of_string;
    size_t pos = 0;

    //
    // The approximate length (bytes) of the decoded string might be one ore
    // two bytes smaller, depending on the amount of trailing equal signs
    // in the encoded string. This approximation is needed to reserve
    // enough space in the string to be returned.
    //
    size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
    std::vector<T> ret;
    ret.reserve(approx_length_of_decoded_string);

    while (pos < in_len) {

        unsigned int pos_of_char_1 = pos_of_char(encoded_string[pos + 1]);

        ret.push_back(
                static_cast<T>(((pos_of_char(encoded_string[pos + 0])) << 2) +
                    ((pos_of_char_1 & 0x30) >> 4)));

        if (encoded_string[pos + 2] != '=' && encoded_string[pos + 2] != '.') {
            // accept URL-safe base 64 strings, too, so check for '.' also.

            unsigned int pos_of_char_2 = pos_of_char(encoded_string[pos + 2]);
            ret.push_back(
                    static_cast<T>(((pos_of_char_1 & 0x0f) << 4) + ((
                        pos_of_char_2 & 0x3c) >> 2)));

            if (encoded_string[pos + 3] != '=' && encoded_string[pos + 3] != '.') {
                ret.push_back(
                        static_cast<T>(((pos_of_char_2 & 0x03) << 6) +
                            pos_of_char(encoded_string[pos + 3])));
            }
        }

        pos += 4;
    }

    return ret;
}

int decode(const char *encoded_string, char *string_out) {

    size_t length_of_string = strlen(encoded_string);
    if (!length_of_string)
        return 0;

    size_t in_len = length_of_string;
    size_t pos = 0;

    //
    // The approximate length (bytes) of the decoded string might be one ore
    // two bytes smaller, depending on the amount of trailing equal signs
    // in the encoded string. This approximation is needed to reserve
    // enough space in the string to be returned.
    //
    //size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
    //std::string ret;
    //ret.reserve(approx_length_of_decoded_string);
    char *ret = string_out;

    while (pos < in_len) {

        unsigned int pos_of_char_1 = pos_of_char(encoded_string[pos + 1]);

        *ret++ = (
            static_cast<char>(((pos_of_char(encoded_string[pos + 0])) << 2) +
                ((pos_of_char_1 & 0x30) >> 4)));

        if (encoded_string[pos + 2] != '=' && encoded_string[pos + 2] != '.') {
            // accept URL-safe base 64 strings, too, so check for '.' also.

            unsigned int pos_of_char_2 = pos_of_char(encoded_string[pos + 2]);
            *ret++ = (
                static_cast<char>(((pos_of_char_1 & 0x0f) << 4) + ((
                    pos_of_char_2 & 0x3c) >> 2)));

            if (encoded_string[pos + 3] != '=' && encoded_string[pos + 3] != '.') {
                *ret++ = (
                    static_cast<char>(((pos_of_char_2 & 0x03) << 6) +
                        pos_of_char(encoded_string[pos + 3])));
            }
        }

        pos += 4;
    }

    *ret = '\0';
    return ret - string_out;
}

#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
const int N = 520 * 64;
const int BRANCH = 258;

namespace AC
{
    int Tr[N][BRANCH], Tot = 0, PIdx = 0;
    queue<int> Q;
    int E[N], Fail[N];

    void Init() {
        memset(Tr, 0, sizeof Tr);
        memset(E, 0, sizeof E);
        memset(Fail, 0, sizeof Fail);
        Tot = 0;
        PIdx = 0;
        Q = queue<int>();
    }

    void Insert(const char *s, int len) {
        int u = 0;
        for (int i = 0; i < len; i++) {
            if (!Tr[u][s[i]])
                Tr[u][s[i]] = ++Tot;
            u = Tr[u][s[i]];
        }
        E[u] = ++PIdx;
    }

    void Insert(const string &s) {
        int u = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (!Tr[u][s[i]])
                Tr[u][s[i]] = ++Tot;
            u = Tr[u][s[i]];
        }
        E[u] = ++PIdx;
    }

    template <class T>
    void Insert(const vector<T> &s) {
        int u = 0;
        for (size_t i = 0; i < s.size(); i++) {
            if (!Tr[u][static_cast<size_t>(s[i])])
                Tr[u][static_cast<size_t>(s[i])] = ++Tot;
            u = Tr[u][static_cast<size_t>(s[i])];
        }
        E[u] = ++PIdx;
    }

    void Build() {
        for (int i = 0; i < BRANCH; i++)
            if (Tr[0][i])
                Q.push(Tr[0][i]);
        while (!Q.empty()) {
            const int u = Q.front();
            Q.pop();
            for (int i = 0; i < BRANCH; i++) {
                if (Tr[u][i])
                    Fail[Tr[u][i]] = Tr[Fail[u]][i], Q.push(Tr[u][i]);
                else
                    Tr[u][i] = Tr[Fail[u]][i];
            }
        }
    }

    int Ans[520];

    int Query(const char *t, int len) {
        memset(Ans, 0, sizeof Ans);
        int u = 0, res = 0;
        for (int i = 0; i < len; i++) {
            u = Tr[u][t[i]]; // 转移
            for (int j = u; j && E[j] != -1; j = Fail[j]) {
                if (E[j]) {
                    res++;
                    Ans[E[j]]++;
                    //E[j] = -1;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 520; i++) {
            if (Ans[i])
                cnt++;
        }
        return cnt;
    }

    int Query(const string &t) {
        memset(Ans, 0, sizeof Ans);
        int u = 0, res = 0;
        for (size_t i = 0; i < t.size(); i++) {
            u = Tr[u][t[i]]; // 转移
            for (int j = u; j && E[j] != -1; j = Fail[j]) {
                if (E[j]) {
                    res++;
                    Ans[E[j]]++;
                    //E[j] = -1;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 520; i++) {
            if (Ans[i])
                cnt++;
        }
        return cnt;
    }

    template <class T>
    int Query(const vector<T> &t) {
        memset(Ans, 0, sizeof Ans);
        int u = 0, res = 0;
        for (size_t i = 0; i < t.size(); i++) {
            u = Tr[u][static_cast<size_t>(t[i])]; // 转移
            for (int j = u; j && E[j] != -1; j = Fail[j]) {
                if (E[j]) {
                    res++;
                    Ans[E[j]]++;
                    //E[j] = -1;
                }
            }
        }
        int cnt = 0;
        for (int i = 0; i < 520; i++) {
            if (Ans[i])
                cnt++;
        }
        return cnt;
    }
} // namespace AC
#define CPP_IO
#ifdef CPP_IO
string E;
#else
char P[5050];
char E[5050];
char S[5050];
#endif

int main() {
    int n, l;
    #ifdef CPP_IO
    while (cin >> n) {
        #else
    while (scanf("%d", &n) != EOF) {
        #endif
        AC::Init();
        for (int i = 1; i <= n; i++) {
            #ifdef CPP_IO
            cin >> E;
            #else
            scanf("%s", E);
            #endif
            AC::Insert(decode<int>(E));
        }
        AC::Build();
        int m;
        #ifdef CPP_IO
        cin >> m;
        #else
        scanf("%d", &m);
        #endif
        for (int i = 0; i < m; i++) {
            #ifdef CPP_IO
            cin >> E;
            #else
            scanf("%s", E);
            #endif
            printf("%d\n", AC::Query(decode<int>(E)));
        }
        puts("");
    }
    return 0;
}
