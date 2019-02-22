#include <stdio.h>
#include <string.h>
//结构体

struct Books
{
	char title[50];
	char author[50];
	char subject[50];
	int book_id;
};

void writeBook( struct Books book )
{
	printf("title : %s\n", book.title);
	printf("author : %s\n", book.author);
	printf("subject : %s\n", book.subject);
	printf("book_id : %d\n", book.book_id);

	return ;
}

int main(int argc, char const *argv[])
{
	//结构体
	struct Books book1;

	strcpy( book1.title, "PHP");
	strcpy( book1.author, "PHP大牛");
	strcpy( book1.subject, "编程语言");
	book1.book_id = 1;

	writeBook(book1);

	//初始化
	struct Books book2 = {"HTML","HTML大牛","标记语言",2};

	writeBook(book2);

	//位域
	struct bs
	{
		unsigned int status:1;
		unsigned int z:1;
		int length:4;
	};

	struct bs data;

	data.status = 1;
	data.length = 5;
	data.z = 0;

	printf("data.status = %d\n", data.status);
	printf("data.length = %d\n", data.length);
	printf("data.z = %d\n", data.z);

	printf("sizeof(bs) = %d\n", sizeof(struct bs));
	printf("sizeof(data) = %d\n", sizeof(data));
	printf("sizeof(struct Books) = %d\n", sizeof(struct Books));

	typedef struct {
		char str;
		char str1;
		int num;
	} size_1;

	size_1 zz = {'a','b',123};

	printf("zz.str = %c zz.str1 = %c zz.num = %d\n", zz.str, zz.str1, zz.num);

	printf("sizeof(size_1) = %d\n", sizeof(size_1) );

	return 0;

}