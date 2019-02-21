#include <stdio.h>

int x = 2, y = 1, i;

int addtwonum(void)
{
    // 函数内声明变量 x 和 y 为外部变量
    extern int x;
    extern int y;
    // 给外部变量（全局变量）x 和 y 赋值
    x = 1;
    y = 2;
    return x+y;
}

int main(int argc, char const *argv[])
{
	
	//变量定义
	int a = 0, b;
	char c = 'a', ch;
	float f = 0.1, s;
	double d = 1.32121635465;

	printf("int a=%d b=%d\n", a, b);
	printf("char c=%c ch=%c\n", c, ch);
	printf("float f=%f s=%f\n", f, s);
	printf("double d=%f\n",d);

	//变量声明
	extern int i;
	i=5;
	//定义与初始化
	int k = 10; 

	printf("int i=%d k=%d\n", i, k);

	int result;
	result = addtwonum();

	printf("result = %d\n", result);

	return 0;
}