#include <iostream>
#include <vector>
#include <set>
using namespace std;

void solve()
{
    int n;
    cin >> n;
    int a[n];
    vector<int> answer;
    set<int> mn;
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    for(int i = n - 1; i >= 0; i--)
    {
        if(!mn.contains(a[i])){
            mn.insert(a[i]);
            answer.push_back(a[i]);
        }
    }
    int size = answer.size();
    cout << size << endl;
    for(int i = size - 1; i >= 0; i--)
    {
        cout << answer[i] << " ";
    }
}


int main() {
    solve();

    return 0;
}
