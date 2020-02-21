#include <iostream>
#include <stdlib.h>
using namespace std;
int check(int n)
{
	int result = 0;
	if (n % 2 == 0)
	{
		result = 1;
	}
	else
	{
		result = 0;
	}
	return result;
}
int check_prime(int n)
{
	int result = 0;
	if (n == 3 || n == 2 || n == 1 || n == 0) result = 1;
	else
	{
		for (int i = 2;i <= sqrt(n);i++)
		{
			if (n % i == 0)
			{
				result = 0;
				break;
			}
			else
			{
				result = 1;
			}
		}
	}
	return result;
}
int main()
{
	int totalnumber = 100;
	int result = 0;
	for (int i = 0;i < totalnumber;i++)
	{
		result = check_prime(i);
		if (result == 1)
		{
			cout << "the number is:" << i << endl;
		}
	}
	system("pause");
	return 0;
}