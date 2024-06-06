#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	cin >> s;
	int ans = 0;
	for (int i = 0; i < s.length(); i++)
		if (s[i] == '4' or s[i] == '7') ans++;
	if (ans == 4 or ans == 7) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}