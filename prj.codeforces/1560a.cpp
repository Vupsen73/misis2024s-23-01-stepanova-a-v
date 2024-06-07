#include<iostream>

int main()
{
    int t;
    int n;
    int i;
    int cnt;
    std::cin >> t;
    while (t--)
    {
        cnt = 1;
        i = 1;
        std::cin >> n;
        while (cnt <= n)
        {
            if (i % 10 != 3 && i % 3 != 0)
            {
                cnt++;
            }
            i++;
        }
        std::cout << --i << std::endl;
    }
}
