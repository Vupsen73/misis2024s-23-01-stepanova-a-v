#include <iostream>
#include <cmath>
using namespace std;

size_t count_discharge_num(int num)
{
	size_t discharge_counter = 0;
	while (num > 0)
	{
		num /= 10;
		discharge_counter++;
	}

	return discharge_counter;
}

int main()
{
	int nums_count = 0;
	cin >> nums_count;

	int* num_arr = new int[nums_count];

	for (int i = 0; i < nums_count; i++) {
		cin >> num_arr[i];
	}

	for (int i = 0; i < nums_count; i++) {
		size_t discharge_count = count_discharge_num(num_arr[i]);
		size_t k = 0;
		for (int j = 0; j < discharge_count; j++)
		{
			int num_in_dis = num_arr[i] / (int)pow(10, j) % 10;
			if (num_in_dis != 0)
				k++;
		}

		cout << k << endl;

		for (int j = discharge_count - 1; j >= 0; j--)
		{
			int num_in_dis = num_arr[i] / (int)pow(10, j) % 10;
			if (num_in_dis != 0)
				cout << num_in_dis * (int)pow(10, j) << " ";
		}

		cout << "\n";
	}

	delete num_arr;
}
