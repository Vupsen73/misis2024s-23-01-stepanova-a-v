#include <iostream>
using namespace std;
int main()
{
    int k, i, n, s = 0;
    int a[50];
    cin >> n >> k;
    for (i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (i = 1; i <= n; i++)
    {
        if (a[i] >= a[k] && a[i] != 0)
            s++;
    }
    cout << s;
}