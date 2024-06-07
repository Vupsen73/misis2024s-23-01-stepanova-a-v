#include <iostream> 
#include<string>


void code() {
	std::string s;
	std::string c = "codeforces";
	std::cin >> s;
	int x = 0;
	for (int i = 0; i < 10; i++) 
	{
		if (s[i] != c[i])
		{
			x++;
		}
	}
	std::cout << x << std::endl;
}


int main() {
	int t = 1;
	std::cin >> t;
	while (t--) 
	{
		code();
	}
}
