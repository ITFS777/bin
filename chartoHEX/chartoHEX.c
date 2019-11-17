#include <stdio.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////
#define length 16
void print_str(const char* str, const int num);
void tab(const long long int num);
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	volatile char ch = '\0';
	volatile long long int count = 0;
	char str[length] = { '\0' };

	while (1)
	{
		count = 0;

		while ((ch = getchar()) != '\n')
		{
			if ((count % 16) == 0)
			{
				printf("%05X-", count);
				printf("%05X | ", (count + 16LL));
			}

			printf("%X ", ch);
			str[count % 16] = ch;
			count++;

			if ((count % 8 == 0) && (count % 16 != 0) && count != 0)
				printf("\b-");

			if ((count % 16) == 0 && count != 0)
			{
				print_str(str, length);
				printf("\n");
				memset(str, '\0', length);
			}
		}

		tab(count);
		print_str(str, length);

		if (str[0] != '\0')
			printf("\n");
		memset(str, '\0', length);
	}
}
void print_str(const char* str,const int num)
{
	if (str[0] == '\0')
		return 0;

	int i = 0;

	if (str[0] == '\0')
		return 0;
	printf("|");

	for (i = 0; i < num; i++)
		if(str[i] == '\0')
			printf(" .");
		else
			printf(" %c", str[i]);
}
void tab(const long long int num)
{
	if (num == 0)
		return 0;

	int space = num % 16;
	int i = 0;

	if (space != 0)
		for (i = 0; i < 16 - space; i++)
			printf("%02X ", 0);
}