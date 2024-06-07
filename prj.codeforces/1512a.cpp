#include<iostream>
#include<algorithm>

int main() 
{
    int a;
    std::cin >> a;
    while (a != 0) 
    {
        int b;
        std::cin >> b;
        int arr[b];
        for (int i = 0; i < b; i++) 
        {
            std::cin >> arr[i];
        }
        for (int i = 0; i < b; i++) 
        {
            int c = std::count(arr, arr + b, arr[i]);
            if (c == 1) 
            {
                std::cout << i + 1 << std::endl;
            }
        }
        a--;
    }
    return 0;
}
