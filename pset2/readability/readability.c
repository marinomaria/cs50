#include <stdio.h>
#include "libcs50-10.1.0\src\cs50.h"
#include <string.h>
#include <ctype.h>
#include <math.h>

void count_everything(string t, int *countsArr);
int get_coleman_liau(int l, int w, int s);

int main(void)
{
    string text = get_string("Text: ");

    int counts[10] = {0};
    count_everything(text, counts);

    int index = get_coleman_liau(counts[0], counts[1], counts[2]);

    if (index > 1 && index < 16)
    {
        printf("Grade %i", index);
    }
    else if (index < 1)
    {
        printf("Before Grade 1");
    }
    else if (index >= 16)
    {
        printf("Grade 16+");
    }

    printf("\n");
}

void count_everything(string t, int *countsArr)
{
    int countL = 0;
    int countW = 1;
    int countS = 0;

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (isalpha(t[i]))
        {
            countL++;
        }
        if (isblank(t[i]))
        {
            countW++;
        }
        if (t[i] == '.' || t[i] == '?' || t[i] == '!')
        {
            countS++;
        }
    }
    countsArr[0] = countL;
    countsArr[1] = countW;
    countsArr[2] = countS;
}

int get_coleman_liau(int l, int w, int s)
{
    float L = l / (float) w * 100;
    float S = s / (float) w * 100;
    int grade = round(0.0588 * L - 0.296 * S - 15.8);
    return grade;
}