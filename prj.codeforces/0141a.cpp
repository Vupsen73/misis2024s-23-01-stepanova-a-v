#include<iostream>
#include<algorithm>
#include<string>


int main()
{
    std::string a;
    std::string b;
    std::string c;
    std::string d;
    
    std::cin >> a >> b >> c;
    d = a + b;
    sort(d.begin(), d.end());
    sort(c.begin(), c.end());
    if (d == c)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO";
    }
    return 0;
}
