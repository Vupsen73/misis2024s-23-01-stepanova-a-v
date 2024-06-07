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
        if (i % k == 0 || i % l == 0 || i % m == 0 || i % n == 0)
        {
            c++;
        }
    }
    std::cout << c;
}
