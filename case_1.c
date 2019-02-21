#include <stdio.h>
//有1、2、3、4个数字，能组成多少个互不相同且无重复数字的三位数？都是多少？

int main(void)
{

	int max = 5;
	int i,j,k,a = 0;

	for (int i = 1; i < max; i++)
	{
		for (int j = 1; j < max; j++)
		{
			//if( i == j ) continue;
			for (int k = 1; k < max; k++)
			{
				//if( k == i || k == j ) continue;
				a++;
				printf("%d-%d-%d\n", i, j, k );
			}
		}
	}

	printf("%d组三位数\n", a);

	return 0;
}