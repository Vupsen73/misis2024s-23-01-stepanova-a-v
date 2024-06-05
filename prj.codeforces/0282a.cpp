#include<iostream>
using namespace std;
int main() {
	int n, x = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string str;
		cin >> str;
		if (str[1] == '+')  x++;
		else   x--;
	}
	cout << x << endl;
}