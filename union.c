#include <stdio.h>
#include <string.h>
//共用体

union Data {
	int i;
	float f;
	char str[50];
};

int main(int argc, char const *argv[])
{

	union Data data;

	printf("sizeof( union Data ) %d\n", sizeof(union Data));

	data.i = 12;
	printf("data.i = %d\n", data.i);

	data.f = 3.1415;
	printf("data.f = %f\n", data.f);

	strcpy(data.str, "何必丶丶");
	printf("data.str = %s\n", data.str);

	return 0;
}
