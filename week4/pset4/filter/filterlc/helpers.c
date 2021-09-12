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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    // Declare variables for original and sepia colors
    BYTE originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            // Calculate needed RGB values with a sepia algorithm and assign that value to bytes of the same pixel
            sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
            sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);

            // Check if values are not over RGB limit and then write them to the pixel channels
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = sepiaBlue;
            }

            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = sepiaGreen;
            }

            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = sepiaRed;
            }
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
