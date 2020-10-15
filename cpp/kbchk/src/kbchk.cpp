#include <cstdio>
// Here is the header file for Windows which is not installed in linux/macOS.
#include <conio.h>
////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    char key;
    while((key = getch())!=27)
        printf("%d\n",key);
}
