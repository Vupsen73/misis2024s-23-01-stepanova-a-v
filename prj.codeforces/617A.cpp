#include <iostream>
int main() {
	int s;
	std::cin >> s;
	if (s%5 != 0 && s >= 1 && s <= 1000000) {
		std::cout << (s / 5) + 1;
	}
	else if (s % 5 == 0) {
		std::cout << s/5;
	}
	return 0;
}