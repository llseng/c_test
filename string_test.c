#include <stdio.h>
#include <string.h>
#include <windows.h>

//初始函数
int main(int argc, char const *argv[])
{
	int i = 0;

	printf("当前进度0%%");
	while(i<=100)
	{
		Sleep(10);
		if( i<=10 )
		{
			printf("\b\b");
		}else{
			printf("\b\b\b");
		}
		printf("%d%%", i);
		fflush( stdout );
		i++;
	}

	return 0;
}