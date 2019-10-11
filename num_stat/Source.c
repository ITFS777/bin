#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
int main(void)
{
    int i = 0, j = 0, count = 0, max = 0, min = 0, level_count = 0,flag = 0;
    float step = 0;

    while (~scanf(" %d %d", &count, &level_count))
    {
        if (count == 0)
            return 0;
        int *str = (int *)calloc(count, sizeof(int));
        memset(str, 0, count * sizeof(int));

        for (i = 0; i < count; i++)
            scanf(" %d", &str[i]);

        for (i = 0, max = str[0], min = str[0]; i < count; i++)
        {
            if (str[i] > max)
                max = str[i];
            if (str[i] < min)
                min = str[i];
        }

        step = (max - min) / 6.0;
        printf("Max: %d\nMin: %d\nRange: %d\nStep: %f\n", max, min, max - min, step);

        for (i = 0; i < count; i++)
        {
            for (j = 0; j < level_count; j++)
            {
                if (j == (level_count - 1))
                    if (str[i] >= (min + (step * j)) && str[i] <= max)
                        {
                            printf("%d ",j);
                            continue;
                        }

                if (str[i] >= (min + (step * j)) && str[i] < (min + step * (j + 1)))
                            printf("%d ",j);
            }
        }
    }

    return 0;
}
/*if (str[i] >= min + step * 0 && str[i] < min + step * 1)
                printf("0 ");
            else if (str[i] >= min + step * 1 && str[i] < min + step * 2)
                printf("1 ");
            else if (str[i] >= min + step * 2 && str[i] < min + step * 3)
                printf("2 ");
            else if (str[i] >= min + step * 3 && str[i] < min + step * 4)
                printf("3 ");
            else if (str[i] >= min + step * 4 && str[i] < min + step * 5)
                printf("4 ");
            else if (str[i] >= min + step * 5 && str[i] <= max)
                printf("5 ");
            else
                printf("error ");*/