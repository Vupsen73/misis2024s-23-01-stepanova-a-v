#include <iostream>


int main() {
    int n;
    int k;
    std::cin >> n;
    int arr[n + 1];

    for (int i = 1; i <= n; i++) 
    {
        std::cin >> k;
        arr[k] = i;
    }
    for (int i = 1; i <= n; i++) 
    {
        std::cout << arr[i] << " ";
    }
  
}