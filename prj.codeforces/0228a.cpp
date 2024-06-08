#include <iostream>
#include <set>

int main()
{
	int s;
	std::set<int> st;
	for (int i = 0; i < 4; i++) 
	{
		std::cin >> s;
		st.insert(s);
	}
	std::cout << 4 - st.size() << std::endl;
}
