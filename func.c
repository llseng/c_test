#include <stdio.h>

//传值调用
int max(int num, int num2)
{
	int result;

	if( num > num2 )
	{
		result = num;
	}else{
		result = num2;
	}

	return result;
}

//引用调用
void swap(int *x, int *y)
{
	int temp;

	temp = *x;

	*x = *y;

	*y = temp;

	return ;
}

int main(int argc, char const *argv[])
{

	int a,b;

	a = 123;
	b = 456;

	printf("a = %d b = %d\n", a, b);

	printf("a b 最大的是%d\n", max(a,b));

	//调换
	swap(&a,&b);

	printf("数值调换后 a = %d b = %d\n", a, b);

	/* code */
	return 0;
}