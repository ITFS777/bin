#include <stdio.h>
#include <string.h>
//////////////////////////////////////////////////////////////////////////
#define length 16								//每行字符个数
void print_str(const char *str, const int num); //打印字符序列
void tab(const long long int num);				//补全空行
//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	volatile unsigned char ch = '\0';
	volatile long long int count = 0;
	unsigned char str[length] = {'\0'};

	while (1)
	{
		count = 0;

		while ((ch = getchar()) != '\n')
		{
			if ((count % 16) == 0) //判断行首并打印序号
				printf("%05X | ", count);

			printf("%02X ", ch); //打印字符对应的HEX
			str[count % 16] = ch;
			++count;

			if ((count % 8 == 0) && (count % 16 != 0) && (count != 0))
				printf("\b-"); //打印分隔符

			if (((count % 16) == 0) && (count != 0)) //判断行尾
			{
				print_str(str, length); //打印对应ASCII序列
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
void print_str(const char *str, const int num)
{
	if (str[0] == '\0') //判断是否为空行
		return 0;

	int i = 0;
	printf("|");

	for (i = 0; i < num; ++i)
		if (str[i] == '\0')
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
		for (i = 0; i < 16 - space; ++i)
		{
			printf("%02X ", 0);
			if ((space <= 8) && (i == 7 - space))
				printf("\b-"); //打印分隔符
		}
}