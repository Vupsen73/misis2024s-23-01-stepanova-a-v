#include <iostream>
using namespace std;
int main() {
    int k, n, w = 0;
    cin >> k >> n >> w;
    int a = k * w * (w + 1) / 2;
    if (a > n) {
        cout << a - n;
    }
    else cout << 0;
}