#include <stdio.h>
#include <string.h>
//typedef 可以定义类型缩写

//年龄不可能出现负数, 用 age 定义用于年龄的INT类型
typedef unsigned int age;

typedef struct Books{
	unsigned int id;
	char title[50];
	char author[50];
	char subject[50];
} Book;

void printBook( Book *book );

//定义字符串别名
typedef char string[50];

//定义数组别名
typedef char strarr[][50];

int main(int argc, char const *argv[])
{
	Book book;

	book.id = 1;
	strcpy(book.title, "C语言");
	strcpy(book.author, "C语言大牛");
	strcpy(book.subject, "编程语言");

	printBook(&book);

	string str = "这是干嘛呢??";

	printf("str = %s\n", str);

	strarr sarr = {
		"asdasd",
		"sdasdsd",
		"asdasdasda"
	};

	for (int i = 0; i < 3; ++i)
	{
		printf("sarr[%d] %s\n", i, sarr[i]);
	}
}

void printBook( Book *book )
{
	printf("id : %u\n", book->id);
	printf("title : %s\n", book->title);
	printf("auther : %s\n", book->author);
	printf("subject : %s\n", book->subject);

	return;
}