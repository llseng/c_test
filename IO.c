#include <stdio.h>
#include <string.h>
//输入&输出

void test_scanf(void);

void test_getcahr(void);

void test_gets(void);

int main(int argc, char const *argv[])
{
	
	printf(" C语言学习 I/O \n");

	//test_scanf();

	//test_getcahr();

	test_gets();

	return 0;
}

void test_gets(void)
{
	char str[100];

	printf("请输入你的想法 \n");

	gets( str );

	printf("一点用都没有 \n");

	puts( str );

	return ;
}

void test_scanf(void)
{
	float f = 0;

	printf("请输入一个float数 \n");

	//%f 匹配float数据,赋值到f
	scanf("%f", &f);

	printf("value = %f\n", f);

	return;
}

void test_getcahr(void)
{

	// getchar() putchar(int)
	int ch;

	printf("getchar() \n");

	ch = getchar();

	printf("putchar \n");

	putchar(ch);printf("\n");

	return;
}