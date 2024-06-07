#include <iostream>

int main()
{
    int k;
    int l;
    int m;
    int n;
    int d;
    std::cin >> k >> l >> m >> n >> d;
    int c = 0;
    for (int i = 1; i <= d; i++)
    {
        if (i % k == 0 or i % l == 0 or i % m == 0 or i % n == 0)
        {
            c++;
        }
    }
    std::cout << c;
}
