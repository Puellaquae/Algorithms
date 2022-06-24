#include <deque>
#include <string>
#include <iostream>
using namespace std;

class TextEditor {
    deque<char> l;
    deque<char> r;
    string tenLeft() {
        int ll = l.size();
        int s = (ll - 10) > 0 ? (ll - 10) : 0;
        string res;
        for (; s < ll; s++) {
            res.push_back(l[s]);
        }
        return res;
    }
public:
    TextEditor() {}

    void addText(string text) {
        for (char c : text) {
            l.push_back(c);
        }
    }

    int deleteText(int k) {
        int i = 0;
        while (!l.empty() && i < k) {
            l.pop_back();
            i++;
        }
        return i;
    }

    string cursorLeft(int k) {
        int i = 0;
        while (!l.empty() && i < k) {
            r.push_front(l.back());
            l.pop_back();
            i++;
        }
        return tenLeft();
    }

    string cursorRight(int k) {
        int i = 0;
        while (!r.empty() && i < k) {
            l.push_back(r.front());
            r.pop_front();
            i++;
        }
        return tenLeft();
    }
};

int main() {
    TextEditor t;
    t.addText("leetcode");
    cout << t.deleteText(4) << endl;
    t.addText("practice");
    cout << t.cursorRight(3) << endl;
    cout << t.cursorLeft(8) << endl;
    cout << t.deleteText(10) << endl;
    cout << t.cursorLeft(2) << endl;
    cout << t.cursorRight(6) << endl;
}