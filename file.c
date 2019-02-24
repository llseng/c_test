#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <windows.h>
//文件读写

//错误号
extern int errno;
//错误打印
void writeError(void);

int main(int argc, char const *argv[])
{
	printf("ANSI: %d\n", __STDC__);
	char *test = "test.txt";
	char *log = "log.log";

	time_t start, stop;
	DWORD sa, st;
	
	//文件流
	FILE * testFile = NULL;
	FILE * logFile = NULL;

	//a+ 模式为追加  w 清空原有文件 文件不存在则创建
	testFile = fopen(test, "w");
	//r 打开已有文件,模式 只读 指针在开头
	logFile = fopen(log, "r");
	if( logFile == NULL )
	{
		writeError();
	}

	//读取字符串
	char readStr[100];

	time(&start);
	sa = GetTickCount();
//int i = 0;
	//fgets(readStr, 100, logFile);
	while( fgets(readStr, 100, logFile) != NULL)
	{

		//写入到 testFile 失败
		if( fputs(readStr, testFile) < 0 )
		{
			writeError();
		}

//if( i++ > 10 ) break;
	}
	time(&stop);
	st = GetTickCount();

	printf("用时 %ld 秒\n", stop - start);
	printf("用时 %ld 豪秒\n", st - sa);

	//关闭打开的文件流
	fclose(testFile);
	fclose(logFile);

	return 0;
}

void writeError(void)
{
	int errnum;
	errnum = errno;

	printf("错误号: %d\n", errnum);
	printf("错误信息: %s\n", strerror(errnum) );
	perror("-错误信息");

	exit(-1);
	return ;
}