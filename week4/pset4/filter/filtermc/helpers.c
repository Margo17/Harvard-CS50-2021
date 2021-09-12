#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            // Calculate average pixel rgb value and assign that value to bytes of the same pixel
            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare temporary variables
    BYTE tempRed, tempGreen, tempBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {

            // Changing pixels using a temporary variable
            tempBlue = image[i][j].rgbtBlue;
            tempGreen = image[i][j].rgbtGreen;
            tempRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;

            image[i][width - j - 1].rgbtBlue = tempBlue;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtRed = tempRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // Temporary image declaration
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float totalRed = 0, totalGreen = 0, totalBlue = 0;

            // Looking at neighbouring cells
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Summing channel values
                    totalRed += image[i + k][j + l].rgbtRed;
                    totalGreen += image[i + k][j + l].rgbtGreen;
                    totalBlue += image[i + k][j + l].rgbtBlue;
                    count++;
                }
            }

        // After examining neighbouring cells calculating average color value and assigning it to temporary image
        temp[i][j].rgbtRed = round(totalRed / count);
        temp[i][j].rgbtGreen = round(totalGreen / count);
        temp[i][j].rgbtBlue = round(totalBlue / count);
        }
    }

    // Copying temporary image to the real one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Temporary image declaration
    RGBTRIPLE temp[height][width];

    // Copying image to the temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through rows
    for (int i = 0; i < height; i++)
    {

        // Loop through columns
        for (int j = 0; j < width; j++)
        {

            // Declare ints and assign value
            float Gx_red, Gx_blue, Gx_green, Gy_red, Gy_blue, Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;

            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }

                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }

                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }

            // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));

            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}