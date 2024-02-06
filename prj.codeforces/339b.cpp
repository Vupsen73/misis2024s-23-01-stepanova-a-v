#include <iostream>
using namespace std;

int main() {
    int n,m;
    cin >> n >> m;
    int dest;
    int curr = 1;
    long long result = 0;
    for(int i = 0; i < m; i ++)
    {
        cin >> dest;
        if(dest >= curr)
        {

            result += dest - curr;
        }else
        {
            result += n - curr + dest;
        }
        curr = dest;
    }
    cout << result;


    return 0;
}
