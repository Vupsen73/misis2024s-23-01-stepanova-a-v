#include<iostream>
#include<set>
using namespace std;

int main()
{
    int n, w, x, y;
    cin >> n;
    set<int> s;
    cin >> x;
    while (x--)
    {
        cin >> w;
        s.insert(w);
    }
    cin >> y;
    while (y--) {
        cin >> w;
        s.insert(w);
    }
    if (s.size() == n)
    {
        cout << "I become the guy.";
    }
    else cout << "Oh, my keyboard!";
}