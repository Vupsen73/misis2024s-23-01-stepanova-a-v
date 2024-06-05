#include <iostream>
#include <algorithm>
using namespace std;
int main() {
    string s, p = "";
    cin >> s;
    sort(s.begin(), s.end());
    for (int i = (s.size() / 2); i < s.size(); i++) {
        p += s[i];
        p += '+';
    }
    p.pop_back();
    cout << p;
}