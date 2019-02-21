#include <stdio.h>
//指针

int main(int argc, char const *argv[])
{
	//指针定义与使用
	int var1;
	char var2[10] = "何必";

	printf("var1 变量地址: %p\n", &var1);
	printf("var2 变量地址: %p\n", &var2);

	printf("%s\n", var2);

	int var = 20;

	int *ip;

	ip = &var;

	printf("var 变量地址: %p\n", &var);
	printf("ip 变量地址: %p\n", ip);
	printf("*ip = %d\n", *ip);

	int arr[5] = {21,515,6,8,156};
	int *p,**pp;

	p = arr;
	pp = &p;

	printf("arr 变量地址%p\n", arr);
	printf("&arr 变量地址%p\n", &arr);
	printf("p 变量地址%p\n", p);
	printf("pp 变量地址%p\n", pp);
	
	printf("*p = %d\n", *p);
	printf("**pp = %d\n", **pp);

	//空指针
	int *ptr = NULL;

	printf("ptr 变量地址: %p\n", ptr);

	return 0;

}
