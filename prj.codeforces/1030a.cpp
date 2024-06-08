#include <iostream>

int main() {
    int n;
    int a;
    std::cin >> n;
    for (int i = 0; i < n; i++) 
    {
        std::cin >> a;
        if (a == 1) 
        {
            std::cout << "HARD";
            return 0;
        }
    }
    std::cout << "EASY";
}