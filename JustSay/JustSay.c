#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
//////////////////////////////////////////////////////////////////////////
#define PATH "S:\\ITFS\\Diary.txt"
#define SIZE 1024
//////////////////////////////////////////////////////////////////////////
char *get_time(void);
//////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
	int flag = 0;
	char *str[SIZE] = {'\0'};
	FILE *fp = fopen(PATH, "a");
	if (fp == NULL)
	{
		printf("error\n");
		return 0;
	}

	while (1)
	{
		memset(str, '\0', SIZE * sizeof(char));
		fgets(str, SIZE, stdin);

		if(str[0] == '\n')
			return 0;

		fputs(get_time(), fp);
		flag = fputs(str, fp);

		system("CLS");

		if (flag != EOF)
		{
			printf("INFO: Write Succeed\n");
			continue;
		}
		else
		{
			printf("INFO: Write Error\n");
			continue;
		}
	}

	return 0;
}
//////////////////////////////////////////////////////////////////////////
char *get_time(void)
{
	time_t *ptm = (time_t)malloc(sizeof(long long));
	time(ptm);
	struct tm *tmpt = localtime(ptm);
	free(ptm);
	ptm = NULL;
	return asctime(tmpt);
}