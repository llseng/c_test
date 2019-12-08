#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void test1(void);

struct Scs
{
	size_t num;
	char *file;
};


int main(void)
{
	test1();return 0;

	FILE * file = NULL;

	file = fopen("extern.c", "r");

	if( file == NULL )
	{
		printf("文件打开失败\n");
		return 0;
	}

	char row[100];

	char const *list[100];

	int li = 0;

	printf("%d\n", sizeof(char *));

	while(fgets(row, 100, file) != NULL)
	{
		//printf("%d\n", strlen(row));
		if( strlen(row) == 1 && row[strlen(row)-1] == '\n' )
		{
			continue;//printf("%s\n", row);
		}
		
		//printf("%s", row);
		list[li] = row;
		li++;
		
	}

	for (int i = 0; i < li; i++)
	{
		printf("%s", list[i]);
	}

	fclose(file);

}

//
void test1(void)
{

	char str[] = "123456789";

	printf("%s\n", str);
	printf("%d\n", sizeof str);

	return ;
}
