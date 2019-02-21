#include <stdio.h>

int count;

extern void write_extern(void);

int main(int argc, char const *argv[])
{

	count = 15;
	write_extern();

}