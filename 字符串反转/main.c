#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
int main(void)
{
	int i = 0, length = 1;
	char* ch = (char*)calloc(2, sizeof(char));
	memset(ch, '\0', sizeof(char) * 2);
	while (1)
	{
		length = 0;
		char* str = (char*)calloc(1, sizeof(char));
		memset(str, '\0', sizeof(char));
		while ((ch[0] = getchar()) != '\n')
		{
			str = realloc(str, (++length + 1) * sizeof(char));
			if (str == NULL)
				return 0;
			str[length] = '\0';
			strncat(str, ch, sizeof(char));
			memset(ch, '\0', sizeof(char) * 2);
			
		}
		for (i = length - 1; str[i - 1] != '\0'; i--)
			putchar(str[i]);
		printf("\n");
		free(str);
	}
	return 0;
}