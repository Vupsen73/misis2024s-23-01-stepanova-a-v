#include<iostream>
#include<algorithm>

int main()
{
    int x;
    int y;
    std::cin >> x >> y;
    std::cout << std::min(x, y) << " " << abs(x - y) / 2;
}
