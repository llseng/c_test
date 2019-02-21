#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//数组

//传递一维数组给函数
int sum(int arr[], int n)
{
	int sum = 0;

	for (int i = 0; i < n; ++i)
	{
		sum += arr[i];
	}

	return sum;

}

int sum2(int *arr, int n)
{
	int sum = 0;

	for (int i = 0; i < n; ++i)
	{
		sum += arr[i];
	}

	return sum;
}

//传递二维数组给函数
int Sum(int *arr, int n, int m)
{
	int sum = 0;

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			//printf("%d\n", *(arr+i*m+j));
			//printf("%d\n", *arr);
			sum += *(arr + i*m+j);
		}
	}

	return sum;
}

//返回二维数组
int * getRandom(void)
{
	
	static int result[10];
	int i;

	//设置种子
	srand( (unsigned)time( NULL ) );
	for (int i = 0; i < 10; ++i)
	{
		result[i] = rand();

		printf("result[%d] = %d\n", i, result[i]);

	}

	return result;
}

//主程序
int main(int argc, char const *argv[])
{

	printf("一维数组\n");

	//一维数组
	int intArr[5] = {1,2,3,4,6};

	for (int i = 0; i < 5; ++i)
	{
		printf("intArr[%d] = %d\n", i, intArr[i]);
	}

	printf("intArr总和为%d\n", sum2(intArr,5));

	char str[50] = "这是一个字符数组";

	printf("str = %s\n", str);

	/* **/
	printf("二维数组\n");

	//二维数组
	int intArray[3][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9},
	};

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			printf("intArray[%d][%d] = %d\t", i, j, intArray[i][j]);
		}

		printf("\n");
	}

	printf("intArray总和为 %d\n", Sum(&intArray[0][0], 3, 3));

	char strArr[5][20] = {"变量","常量","存储类","判断","循环"};

	for (int i = 0; i < 5; ++i)
	{
		printf("strArr[%d] = %s\n", i, strArr[i]);
	}

	//函数返回数组
	int *funcArr;
	funcArr = getRandom();

	for (int i = 0; i < 10; ++i)
	{
		printf("funcArr[%d] = %d\n", i, funcArr[i]);
	}

}
