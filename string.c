#include <stdio.h>
#include <string.h>
//字符串

int main(int argc, char const *argv[])
{
	
	char str[25] = "何必丶丶";
	char str2[25] = "...";
	char str3[25];

	printf("str = %s\n", str);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);

	strcpy(str3,str);

	printf("str = %s\n", str);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);

	strcat(str,str2);

	printf("str = %s\n", str);
	printf("str2 = %s\n", str2);
	printf("str3 = %s\n", str3);

	printf("strlen( str ) = %d\n", strlen(str));
	printf("strcmp( str, str2 ) = %d\n", strcmp(str, str2));

	char *str_1 = strchr( str, '何' );

	printf("strchr( str, '何' ) = %s\n", str_1);

	char *str_2 = strstr(str,"何");

	printf("strstr(str,\"何\") = %s\n", str_2);

	return 0;
}