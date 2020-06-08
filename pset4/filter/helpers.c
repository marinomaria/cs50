#include "helpers.h"
#include <math.h>

//Function prototypes
int cap(int n);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // For every pixel
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor((width + 1) / 2); j++)
        {
            // For every pixel
            int newPos = width - (j + 1);
            RGBTRIPLE temp = image[i][newPos];
            image[i][newPos] = image[i][j];
            image[i][j] = temp;
        }
    }
    return;
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Stores a copy of image on tmp
    RGBTRIPLE tmp[height][width];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            tmp[y][x] = image[y][x];
        }

    }
    int r, g, b, n;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            // For every pixel
            r = 0;
            g = 0;
            b = 0;
            n = 0;
            for (int i = -1; i <= 1; i++)
            {
                if (x + i >= 0 && x + i < width)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (y + j >= 0 && y + j < height)
                        {
                            r += tmp[y + j][x + i].rgbtRed;
                            g += tmp[y + j][x + i].rgbtGreen;
                            b += tmp[y + j][x + i].rgbtBlue;
                            n++;
                        }
                    }
                }
            }
            image[y][x].rgbtRed = round((float) r / n);
            image[y][x].rgbtGreen = round((float) g / n);
            image[y][x].rgbtBlue = round((float) b / n);

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Stores a copy of image on tmp
    RGBTRIPLE tmp[height][width];
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            tmp[y][x] = image[y][x];
        }

    }

    const int max = 9;
    int r[max], g[max], b[max], n;
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            //For every pixel

            // Clear arrays
            for (int i = 0; i < max; i++)
            {
                r[i] = 0;
                g[i] = 0;
                b[i] = 0;
                n = 0;
            }

            for (int i = -1; i <= 1; i++)
            {
                if (x + i >= 0 && x + i < width)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (y + j >= 0 && y + j < height)
                        {
                            r[n] = tmp[y + j][x + i].rgbtRed;
                            g[n] = tmp[y + j][x + i].rgbtGreen;
                            b[n] = tmp[y + j][x + i].rgbtBlue;
                            n++;
                        }
                        else
                        {
                            r[n] = 0;
                            g[n] = 0;
                            b[n] = 0;
                            n++;
                        }
                    }
                }
                else
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        r[n] = 0;
                        g[n] = 0;
                        b[n] = 0;
                        n++;
                    }
                }
            }

            // Declares x and y kernels
            const int xMatrix[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
            const int yMatrix[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

            float xRed = 0.0, xGreen = 0.0, xBlue = 0.0, yRed = 0.0, yGreen = 0.0, yBlue = 0.0;

            for (int i = 0; i < max; i++)
            {
                xRed += r[i] * xMatrix[i];
                xGreen += g[i] * xMatrix[i];
                xBlue += b[i] * xMatrix[i];

                yRed += r[i] * yMatrix[i];
                yGreen += g[i] * yMatrix[i];
                yBlue += b[i] * yMatrix[i];
            }

            // Set new values for every channel
            image[y][x].rgbtRed = cap(round(sqrt(xRed * xRed + yRed * yRed)));
            image[y][x].rgbtGreen = cap(round(sqrt(xGreen * xGreen + yGreen * yGreen)));
            image[y][x].rgbtBlue = cap(round(sqrt(xBlue * xBlue + yBlue * yBlue)));

        }
    }
    return;
}

// Caps value to the max of unsigned int (255)
int cap(int n)
{
    if (n < 256)
    {
        return n;
    }
    else
    {
        return 255;
    }
}