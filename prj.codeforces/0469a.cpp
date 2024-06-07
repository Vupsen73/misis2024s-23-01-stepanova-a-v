#include<iostream>
#include<set>

int main()
{
    int n;
    int w;
    int x;
    int y;
    std::cin >> n;
    std::set<int> s;
    std::cin >> x;
    while (x--)
    {
        std::cin >> w;
        s.insert(w);
    }
    std::cin >> y;
    while (y--) {
        std::cin >> w;
        s.insert(w);
    }
    if (s.size() == n)
    {
        std::cout << "I become the guy.";
    }
    else
    {
        std::cout << "Oh, my keyboard!";
    }
}
