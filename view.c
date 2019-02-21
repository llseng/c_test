#include <stdio.h>
#include <limits.h>
#include <float.h>

//初始函数
int main(int argc, char const *atgv[])
{

	printf("int 储存大小 : %lu \n", sizeof(int) );
	//%lu 为32位无符号整数

	printf("float 储存最大字节数 : %d \n", sizeof(float) );
	printf("float 最小值 : %E \n", FLT_MIN );
	printf("float 最大值 : %E \n", FLT_MAX );
	printf("float 精度值 : %d \n", FLT_DIG );
	//%E 为以指数形式输出单,双精度实数

	return 0;
}