#include <stdio.h>
#include <stdarg.h>
//声明
unsigned int my_sum( unsigned int num, ... );

int main( int argc, const char *argv[] ) {

	unsigned int a;
	unsigned int b;

	a = my_sum(5,4,2,48,216,11);
	b = my_sum(4,3,48,5,11);

	printf( "a: %d; b: %d;\n", a, b );
	return 0;
}

//可变参数测试
unsigned int my_sum( unsigned int num, ... ) {
	unsigned int sum = 0;
	va_list valist;
	int i;
	//第一个参数为参数数量,自身除外
	printf( "num: %d;\n", num );
	va_start( valist, num ); 
	
	for( i = 0; i < num; i++ ) {
		unsigned int li;
		li = va_arg( valist, unsigned int );
		printf( "arg: %d;\n", li );
		sum += li;
	}
	va_end( valist ); //置空
	return sum;
}