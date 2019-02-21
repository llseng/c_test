#include <stdio.h>
//枚举

enum DAY
{
	MON = 1, TUE, WED, THU, FRI, SAT, SUN
};

int main(int argc, char const *argv[])
{

	enum DAY day;

	day = FRI;

	printf("%d\n", day);

	return 0;
}