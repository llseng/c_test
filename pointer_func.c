#include <stdio.h>
#include <stdlib.h>
//函数指针

int max(int x, int y)
{
	int r;

	if( x > y )
	{
		r = x;
	}else{
		r = y;
	}

	return r;
}

//返回随机数
int getRandNum(void)
{
	return rand();
}

void pop_array(int r[],int size,int (*func)(void))
{

	for (int i = 0; i < size; ++i)
	{
		r[i] = func();
	printf("%d\n", r[i]);
	}
	return ;

}

int main(int argc, char const *argv[])
{

	//函数指针
	int (*p)(int,int) = max;
	int a,b,c,d;

	printf( "请输入三个数字" );
	scanf("%d %d %d", &a, &b, &c);

	d = p(p(a,b),c);

	printf("最大数字是: %d\n", d);

	int arr[5];

	pop_array(arr,5,getRandNum);

	for (int i = 0; i < 5; ++i)
	{
		printf("arr[%d] = %d\n", i, arr[i]);	
	}

	return 0;
}