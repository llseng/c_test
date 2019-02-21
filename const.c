#include <stdio.h>

// #define 预处理器 定义常量
#define HIGHT 20
#define WIDTH 15

int main(int argc, char const *argv[])
{
	// const 关键字 定义常量
	const int L_MAX = 10;
	const int L_MIN = 5;
	const char L_CHAR = '\n';

	int area, L;

	area = HIGHT * WIDTH;

	printf("HIGHT = %d\n", HIGHT);
	printf("WIDTH = %d\n", WIDTH);
	printf("area = %d\n", area);

	L = L_MAX * L_MIN;

	printf("L_MAX = %d\n", L_MAX);
	printf("L_MIN = %d\n", L_MIN);
	printf("L = %d\n", L);
	printf("L_CHAR = %c\n", L_CHAR);

	return 0;
}