#include<iostream>

int main() {
    int n = 0;
    int h = 0;
    int a = 0;
    int ans = 0;
    std::cin >> n >> h;
    while (n--)
    {
        std::cin >> a;
        if (a > h)
        {
            ans += 2;
        }
        else
        {
            ans++;
        }
    }
    std::cout << ans << std::endl;
}
