#include <stdio.h>
#include "libcs50-10.1.0\src\cs50.h"

int checksum(long n);
string checkBrand(long n);

int main(void)
{
    long cardNumber = get_long("Number: ");
    //printf("%i\n", checksum(cardNumber)); debugging
    if (checksum(cardNumber) == 0)
    {
        printf("INVALID\n");
    }
    else
    {
        printf("%s\n", checkBrand(cardNumber));
    }
}

//calculates checksum. returns 1 if valid, 0 if invalid.
int checksum(long n)
{
    int sum = 0;

    for (int i = 1; n > 0; i++)
    {
        int digit = (n % 10);

        if (i % 2 == 0 && digit < 5)
        {
            sum += digit * 2;
        }

        else if (i % 2 == 0)
        {
            int x = digit * 2;
            int y = x % 10;
            int z = x / 10;
            sum += (z + y);
        }

        else if (i % 2 == 1)
        {
            sum += digit;
        }

        n /= 10;
    }
    if (sum % 10 == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

string checkBrand(long n)
{
    int digitCount = 0;
    int startingDigits;

    for (int i = 1; n > 0; i++)
    {
        if (n < 100 && n > 9)
        {
            startingDigits = n;
        }
        else if (n < 10)
        {
            digitCount = i;
        }

        n /= 10;
    }

    if ((startingDigits == 34 || startingDigits == 37) && digitCount == 15)
    {
        return "AMEX";
    }
    else if (startingDigits > 50 && startingDigits < 56 && digitCount == 16)
    {
        return "MASTERCARD";
    }
    else if (startingDigits > 39 && startingDigits < 50 && (digitCount == 13 || digitCount == 16))
    {
        return "VISA";
    }
    else
    {
        return "INVALID";
    }
}
