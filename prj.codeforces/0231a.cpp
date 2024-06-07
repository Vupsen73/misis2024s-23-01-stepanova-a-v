#include <iostream>

int main() {
	int x = 0;
	int a = 0;
	int b = 0;
	int c = 0;
	int k = 0;
	std::cin >> x;
	for (int i = 0; i < x; i++) {
		std::cin >> a >> b >> c;
		if (a + b + c > 1) {
			k++;
		}
	}
	std::cout << k;
}
