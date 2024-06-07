#include<iostream>

int main()
{
    int t;
    int n;
    int c1;
    int c2;
    std::cin >> t;
    while (t--)
    {
        std::cin >> n;
        c2 = (n + 1) / 3;
        c1 = n - 2 * c2;

        std::cout << c1 << " " << c2 << std::endl;
    }
   
}