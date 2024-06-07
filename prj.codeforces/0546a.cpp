#include <iostream>

int main() {
    int k = 0;
    int n = 0;
    int w = 0;
    std::cin >> k >> n >> w;
    int a = k * w * (w + 1) / 2;
    if (a > n) 
    {
        std::cout << a - n;
    }
    else
    {
        std::cout << 0;
    }
}
