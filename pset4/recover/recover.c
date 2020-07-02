#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for valid input
    if (!(argc == 2))
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("File does not exist or is empty. \n");
        return 1;
    }

    int n = 0;
    BYTE buf[512];
    FILE *img = NULL;
    char *filename = malloc(8 * sizeof(char));

    while ((fread(buf, sizeof(BYTE), 512, file)) == 512)
    {
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff && (buf[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", n);
            img = fopen(filename, "w");
            fwrite(buf, sizeof(BYTE), 512, img);
            fclose(img);
            n++;
        }
        else if (n != 0)
        {
            img = fopen(filename, "a");
            fwrite(buf, sizeof(BYTE), 512, img);
            fclose(img);
        }

        memset(buf, 0, sizeof(buf));
    }

    free(filename);
    fclose(file);
}
