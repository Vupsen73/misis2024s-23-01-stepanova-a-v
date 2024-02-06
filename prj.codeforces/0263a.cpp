#include <iostream>

using namespace std;
int main()
{
	int matrix[5][5] = {};
	for (int i = 0; i < 5; i++)
		cin >> matrix[i][0] >> matrix[i][1] >> matrix[i][2] >> matrix[i][3] >> matrix[i][4];
	int stroka = 0; int stolbec = 0;
	bool flag = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (matrix[i][j] == 1)
			{
				stroka = i;
				stolbec = j;
				flag = true;
				break;
			}
		}
		if (flag)
			break;
	}


	cout << abs(stroka - 2) + abs(stolbec - 2);
}