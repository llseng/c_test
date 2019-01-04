#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int main(void)
{
	int a;

	a = MessageBox(NULL,"Hello World","Hello",MB_YESNO);
	
	if(a == IDYES)
		MessageBox(NULL,"选择了 YES","hint",MB_OK);
	else
		MessageBox(NULL,"选择了 NO","hint",MB_OK);

	return 0;

}
