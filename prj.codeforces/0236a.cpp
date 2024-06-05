#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    string a;
    cin >> a;
    set<char>b(a.begin(), a.end());
    if (b.size() % 2 == 0)
        cout << "CHAT WITH HER!";
    else
        cout << "IGNORE HIM!";
}