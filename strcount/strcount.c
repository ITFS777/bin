#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////
#define SIZE 128
//////////////////////////////////////////////////////////////////////////
int main(void)
{
	char name[SIZE] = { '\0' };
	int i = 0, count = 0;
	while (1)
	{
		count = 0;
		memset(name, '\0', SIZE * sizeof(char));
		fgets(name, SIZE, stdin);
		for (i = 0; i < strlen(name);i++)
		{
			if (name[i] == '\n')
				break;
			if (name[i] != ' ')
			{
				count++;
				for (/*void*/; name[i] != ' '; i++)
					;
				i--;
			}
		}
		printf("%d\n", count);
	}
}