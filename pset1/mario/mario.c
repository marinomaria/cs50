#include <stdio.h>
#include "libcs50-10.1.0\src\cs50.h"

int main(void)
{
   int n;
   do
   {
        n = get_int("Height: ");
   }
   while (n < 1 || n > 8);

   for (int i = 0; i < n; i++)
   {
       for (int j = 1; j <= n; j++)
       {
           if (j < n - i)
           {
              printf(" ");
           }
           else
           {
           printf("#");
           }
       }

       printf("  ");

       for (int k = 1; k < i + 2; k++)
       {
         printf("#");
       }

       printf("\n");
   }
}