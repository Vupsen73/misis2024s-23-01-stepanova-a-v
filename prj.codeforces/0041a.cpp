#include <iostream>
#include <algorithm>
#include<string>

int main() {
    std::string s;
    std::string d;
    std::cin >> s >> d;
    reverse(d.begin(), d.end());
    if (s == d)
        std::cout << "YES";
    else
        std::cout << "NO";
    return 0;
}
