#include<iostream>

int main() {
    int n;
    std::cin >> n;
    std::cout << 8 + n % 2 << " " << n - 8 - n % 2 << std::endl;
}