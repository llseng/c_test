#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

void test1(void);

int main(void)
{

	test1();
	return 0;
	int a;

	a = MessageBox(NULL,"Hello World","Hello",MB_YESNO);
	
	if(a == IDYES)
		MessageBox(NULL,"选择了 YES","hint",MB_OK);
	else
		MessageBox(NULL,"选择了 NO","hint",MB_OK);

	return 0;

}

//
void test1(void)
{

	int arr[] = {54,51,6859,515,16};
	int *p;
	p = arr;

	printf("%p\n", p);
	printf("%d\n", *p);

	*p = 888;

	printf("%d\n", arr[0]);

	char str[] = "asd1asd\r\nasdasdwa6546561616";

	char *str2;
	str2 = str;

	char ch = '\n';

	char *res;

	res = strchr(str2, ch);
	printf("%s\n", res);
	*res = '\0';

	printf("-//-%d\n", *res);

	return ;
}
