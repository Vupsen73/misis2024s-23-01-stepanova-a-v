#include<iostream>
using namespace std;

int main() {
    int n, h, a, ans = 0;
    cin >> n >> h;
    while (n--)
    {
        cin >> a;
        if (a > h)
            ans += 2;
        else
            ans++;
    }
    cout << ans << endl;
    return 0;
}