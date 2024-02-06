#include <iostream>
using namespace std;

void alg()
{
    int n, m, x, y, d;
    cin >> n >> m >> x >> y >> d;
    if(min(x - 1, m - y) <= d && min(n - x, y - 1) <= d)
    {
        cout << -1;
    }else{
        cout << (m + n) - 2;
    }
    cout << endl;
}
int main() {
    int t;
    cin >> t;
    while(t--)
    {
        alg();
    }

    return 0;
}
