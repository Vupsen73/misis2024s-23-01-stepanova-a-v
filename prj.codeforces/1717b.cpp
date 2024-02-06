#include <iostream>
using namespace std;

void tabl()
{
    int n, k, r, c;
    cin >> n >> k >> r >> c;
    int mod = (r + c)%k;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if((i + j)%k == mod)
            {
                cout << "X";
            }else
            {
                cout << ".";
            }
        }
        cout << endl;
    }
}

int main() {
    int t;
    cin >> t;
    while(t--)
    {
        tabl();
    }


    return 0;
}
