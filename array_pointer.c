#include <stdio.h>
//指向数组的指针

int main(int argc, char const *argv[])
{
	int *p;
	int arr[] = {1,15,651,5,11,5,8,65,56};

	p = arr;

	for (int i = 0; i < 9; ++i)
	{
		
		printf("*(p+%i) = %d\n", i, *(p+i) );
		printf("*(arr+%i) = %d\n", i, *(arr+i) );
	}

	char const *names[] = {
		"aaaaaaa",
		"bbbbbbb",
		"ccccccc",
		"ddddddd"
	};

	for (int i = 0; i < 4; ++i)
	{
		printf("names[%d] = %s\n", i, names[i]);
	}

}
