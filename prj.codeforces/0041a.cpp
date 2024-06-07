#include <iostream>
#include <algorithm>
#include<string>

int main() {
    string s;
    string d;
    std::cin >> s >> d;
    reverse(d.begin(), d.end());
    if (s == d)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
