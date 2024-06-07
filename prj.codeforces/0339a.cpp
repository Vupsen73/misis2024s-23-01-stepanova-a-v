#include<iostream>
#include<algorithm>
#include<string>

int main() 
{
    std::string s = "";
    std::string p = "";
    std::cin >> s;
    sort(s.begin(), s.end());
    for (int i = (s.size() / 2); i < s.size(); i++) 
    {
        p += s[i];
        p += '+';
    }
    p.pop_back();
    std::cout << p;
}
