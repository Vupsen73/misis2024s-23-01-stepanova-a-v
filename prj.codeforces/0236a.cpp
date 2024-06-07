#include <iostream>
#include <set>
#include <string>

int main()
{
    std::string a;
    std::cin >> a;
    std::set<char>b(a.begin(), a.end());
    if (b.size() % 2 == 0)
    {
        std::cout << "CHAT WITH HER!";
    }
    else
    {
        std::cout << "IGNORE HIM!";
    }
}
