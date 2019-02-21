#include <stdio.h>
//static 存储类演示

/* 函数声明 */
void func1(void);

//全局变量 static 是默认的
static int count = 10;

int main(int argc, char const *argv[])
{

	while( count-- )
	{
		func1();
	}

	return 0;

}

void func1(void)
{
	/* 'thingy' 是 'func1' 的局部变量 - 只初始化一次
	* 每次调用函数 'func1' 'thingy' 值不会被重置。
	*/                
	static int thingy=5;

	thingy++;
	
	printf(" thingy 为 %d ， count 为 %d\n", thingy, count);

}