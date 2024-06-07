#include <iostream>

int main()
{
    int k = 0;
    int i = 0;
    int n = 0;
    int s = 0;
    int a[50];
    std::cin >> n >> k;
    for (i = 1; i <= n; i++)
    {
        std::cin >> a[i];
    }
    for (i = 1; i <= n; i++)
    {
        if (a[i] >= a[k] && a[i] != 0)
        {
            s++;
        }
    }
    std::cout << s;
}
