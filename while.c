#include <stdio.h>
//求 100 基数和 偶数和

int main(int argc, char const *argv[])
{

	int length = 100;

	//奇数和
	int odd_sum = 0;
	//偶数和
	int even_sum = 0;

	int odd_num = 1;
	int even_num = 2;

	while( odd_num < length )
	{
		odd_sum = odd_sum + odd_num;
		odd_num += 2;
	}

	while( even_num < length )
	{
		even_sum = even_sum + even_num;
		even_num += 2;
	}

	printf("奇数和为 %d\n偶数和为 %d\n", odd_sum, even_sum);

}