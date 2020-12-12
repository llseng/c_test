#include <tchar.h>
#include <stdio.h>
#include <windows.h>

int main() {
    int result;
    result = MessageBox(0, _T("helo word!"), _T( "test"), MB_OKCANCEL );
    printf("return %d", result);
    return 0;
}