#include <iostream>
int main() {
	setlocale(LC_ALL, "RU");

	int c;
	std::cin >> c;
	if (c % 2 == 0 && c > 2 && c <= 100) {
		std::cout << "YES";
	}else {
		std::cout << "NO";
	}
	return 0;
}