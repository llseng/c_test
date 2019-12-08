#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//文件记录结构
struct Scs
{
	char *file;
	size_t num;
};

int main(int argc, char const *argv[])
{
	if( argc < 2 )
	{
		printf("%s\n", "请输入文件名");
		return 0;
	}
	
	FILE *logFile = NULL;
	logFile = fopen(argv[1],"r");

	if( logFile == NULL )
	{
		printf("%s\n", "文件件不存在,或不可读");
		return 0;
	}

	//记录总数
	unsigned int sc_len = 0;

	//配置条件
	char sc_str[20] = "script_filename";

	//当前行, 上一行.
	char row[1024], rrow[1024] = "";

	while( fgets(row, 1024, logFile) != NULL )
	{
		char* str_start = strstr(row, sc_str);

		if( str_start != NULL )
		{
			sc_len++;
		}

		//当前行赋值为上一行
		strcpy(rrow, row);
	}

	printf("慢执行文件出现吃数 %d次\n", sc_len);

	fclose(logFile);

	return 0;
}