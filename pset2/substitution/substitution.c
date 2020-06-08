#include <stdio.h>
#include "libcs50-10.1.0\src\cs50.h"
#include <string.h>
#include <ctype.h>

int string_is_alpha(string t);
int has_duplicates(string s);
string string_to_lower(string t);
const int ASCII_a = 97;
const int ASCII_A = 65;

int main(int argc, string argv[])
{
// Validates user input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26 || string_is_alpha(argv[1]) == 0 || has_duplicates(argv[1]))
    {
        printf("Key must contain 26 unique alphanumeric characters.\n");
        return 1;
    }

// Converts user's key to lowercase
    string key = string_to_lower(argv[1]);

// Asks for plain text
    string plainText = get_string("plaintext: ");

// Converts and prints each char from plainText into ciphertext.
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plainText); i++)
    {
        char c = plainText[i];

        if (isalpha(c) && islower(c))
        {
            int pos = (int) c - ASCII_a;
            printf("%c", key[pos]);
        }
        else if (isalpha(c))
        {
            int pos = (int) c - ASCII_A;
            printf("%c", (char) toupper(key[pos]));
        }
        else
        {
            printf("%c", c);
        }
    }

// Prints new line and return 0
    printf("\n");
    return 0;
}
// Pass every char from a string to isalpha(). Returns 1 only if all chars passed are alphanumeric.
int string_is_alpha(string t)
{
    for (int i = 0; i < strlen(t); i++)
    {
        if (isalpha(t[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}
// Cheks if a string has duplicate chars. Returns 0 if there are no duplicates.
int has_duplicates(string s)
{
    s = string_to_lower(s);
    for (int i = 0; i < strlen(s); i++)
    {
        for (int j = i + 1; j < strlen(s); j++)
        {
            if (s[i] == s[j])
            {
                return 1;
            }
        }
    }
    return 0;
}
// Pass every char from a string to tolower(). Returns the given string in lowercase.
string string_to_lower(string t)
{
    for (int i = 0; t[i]; i++)
    {
        t[i] = tolower(t[i]);
    }
    return t;
}