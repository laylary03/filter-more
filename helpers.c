#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    int final_number;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = 0;
            average += image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            final_number = (int) round(average / 3);
            image[i][j].rgbtRed = final_number;
            image[i][j].rgbtGreen = final_number;
            image[i][j].rgbtBlue = final_number;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[width];
    int foward_count;
    int j;
    for (int i = 0; i < height; i++)
    {
        for (j = width - 1, foward_count = 0; j > -1; j--, foward_count++)
        {
            if (foward_count < j)
            {
                copy[foward_count].rgbtRed = image[i][foward_count].rgbtRed;
                copy[foward_count].rgbtGreen = image[i][foward_count].rgbtGreen;
                copy[foward_count].rgbtBlue = image[i][foward_count].rgbtBlue;

                image[i][foward_count].rgbtRed = image[i][j].rgbtRed;
                image[i][foward_count].rgbtGreen = image[i][j].rgbtGreen;
                image[i][foward_count].rgbtBlue = image[i][j].rgbtBlue;
            }
            else if (foward_count != j)
            {
                image[i][foward_count].rgbtRed = copy[j].rgbtRed;
                image[i][foward_count].rgbtBlue = copy[j].rgbtBlue;
                image[i][foward_count].rgbtGreen = copy[j].rgbtGreen;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int averageRed;
    int averageBlue;
    int averageGreen;
    float total;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            averageRed = 0;
            averageBlue = 0;
            averageGreen = 0;
            total = 0;

            // upper row
            if (i - 1 >= 0)
            {
                averageRed += image[i - 1][j].rgbtRed;
                averageBlue += image[i - 1][j].rgbtBlue;
                averageGreen += image[i - 1][j].rgbtGreen;
                total++;
                if (j - 1 >= 0)
                {
                    averageRed += image[i - 1][j - 1].rgbtRed;
                    averageBlue += image[i - 1][j - 1].rgbtBlue;
                    averageGreen += image[i - 1][j - 1].rgbtGreen;
                    total++;
                }
                if (j + 1 < width)
                {
                    averageRed += image[i - 1][j + 1].rgbtRed;
                    averageBlue += image[i - 1][j + 1].rgbtBlue;
                    averageGreen += image[i - 1][j + 1].rgbtGreen;
                    total++;
                }
            }

            // Middle row
            averageRed += image[i][j].rgbtRed;
            averageBlue += image[i][j].rgbtBlue;
            averageGreen += image[i][j].rgbtGreen;
            total++;
            if (j - 1 >= 0)
            {
                averageRed += image[i][j - 1].rgbtRed;
                averageBlue += image[i][j - 1].rgbtBlue;
                averageGreen += image[i][j - 1].rgbtGreen;
                total++;
            }

            if (j + 1 < width)
            {
                averageRed += image[i][j + 1].rgbtRed;
                averageBlue += image[i][j + 1].rgbtBlue;
                averageGreen += image[i][j + 1].rgbtGreen;
                total++;
            }

            // Lower row
            if (i + 1 < height)
            {
                averageRed += image[i + 1][j].rgbtRed;
                averageBlue += image[i + 1][j].rgbtBlue;
                averageGreen += image[i + 1][j].rgbtGreen;
                total++;
                if (j - 1 >= 0)
                {
                    averageRed += image[i + 1][j - 1].rgbtRed;
                    averageBlue += image[i + 1][j - 1].rgbtBlue;
                    averageGreen += image[i + 1][j - 1].rgbtGreen;
                    total++;
                }

                if (j + 1 < width)
                {
                    averageRed += image[i + 1][j + 1].rgbtRed;
                    averageBlue += image[i + 1][j + 1].rgbtBlue;
                    averageGreen += image[i + 1][j + 1].rgbtGreen;
                    total++;
                }
            }

            averageRed = (int) round(averageRed / total);
            averageBlue = (int) round(averageBlue / total);
            averageGreen = (int) round(averageGreen / total);

            // copies blurred to paste into the image once all averages for pixels are calculated
            copy[i][j].rgbtRed = averageRed;
            copy[i][j].rgbtBlue = averageBlue;
            copy[i][j].rgbtGreen = averageGreen;
        }
    }

    // pastes copies of blurred pixels into image
    for (int r = 0; r < height; r++)
    {
        for (int p = 0; p < width; p++)
        {
            image[r][p].rgbtRed = copy[r][p].rgbtRed;
            image[r][p].rgbtBlue = copy[r][p].rgbtBlue;
            image[r][p].rgbtGreen = copy[r][p].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int GxRed;
    int GxBlue;
    int GxGreen;
    int GyRed;
    int GyBlue;
    int GyGreen;
    int final_valueRed;
    int final_valueBlue;
    int final_valueGreen;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            GxRed = 0;
            GxBlue = 0;
            GxGreen = 0;
            GyRed = 0;
            GyBlue = 0;
            GyGreen = 0;

            // upper row
            if (i - 1 >= 0)
            {
                // Gx will always be zero at upper middle pixel
                GyRed += -2 * (image[i - 1][j].rgbtRed);
                GyBlue += -2 * (image[i - 1][j].rgbtBlue);
                GyGreen += -2 * (image[i - 1][j].rgbtGreen);

                if (j - 1 >= 0)
                {
                    GxRed += -1 * (image[i - 1][j - 1].rgbtRed);
                    GxBlue += -1 * (image[i - 1][j - 1].rgbtBlue);
                    GxGreen += -1 * (image[i - 1][j - 1].rgbtGreen);

                    GyRed += -1 * (image[i - 1][j - 1].rgbtRed);
                    GyBlue += -1 * (image[i - 1][j - 1].rgbtBlue);
                    GyGreen += -1 * (image[i - 1][j - 1].rgbtGreen);
                }
                if (j + 1 < width)
                {
                    GxRed += image[i - 1][j + 1].rgbtRed;
                    GxBlue += image[i - 1][j + 1].rgbtBlue;
                    GxGreen += image[i - 1][j + 1].rgbtGreen;

                    GyRed += -1 * (image[i - 1][j + 1].rgbtRed);
                    GyBlue += -1 * (image[i - 1][j + 1].rgbtBlue);
                    GyGreen += -1 * (image[i - 1][j + 1].rgbtGreen);
                }
            }

            // Middle row
            if (j - 1 >= 0)
            {
                GxRed += -2 * (image[i][j - 1].rgbtRed);
                GxBlue += -2 * (image[i][j - 1].rgbtBlue);
                GxGreen += -2 * (image[i][j - 1].rgbtGreen);
            }

            if (j + 1 < width)
            {
                GxRed += 2 * (image[i][j + 1].rgbtRed);
                GxBlue += 2 * (image[i][j + 1].rgbtBlue);
                GxGreen += 2 * (image[i][j + 1].rgbtGreen);
            }

            // Lower row
            if (i + 1 < height)
            {
                GyRed += 2 * (image[i + 1][j].rgbtRed);
                GyBlue += 2 * (image[i + 1][j].rgbtBlue);
                GyGreen += 2 * (image[i + 1][j].rgbtGreen);
                if (j - 1 >= 0)
                {
                    GxRed += -1 * (image[i + 1][j - 1].rgbtRed);
                    GxBlue += -1 * (image[i + 1][j - 1].rgbtBlue);
                    GxGreen += -1 * (image[i + 1][j - 1].rgbtGreen);

                    GyRed += image[i + 1][j - 1].rgbtRed;
                    GyBlue += image[i + 1][j - 1].rgbtBlue;
                    GyGreen += image[i + 1][j - 1].rgbtGreen;
                }

                if (j + 1 < width)
                {
                    GxRed += image[i + 1][j + 1].rgbtRed;
                    GxBlue += image[i + 1][j + 1].rgbtBlue;
                    GxGreen += image[i + 1][j + 1].rgbtGreen;

                    GyRed += image[i + 1][j + 1].rgbtRed;
                    GyBlue += image[i + 1][j + 1].rgbtBlue;
                    GyGreen += image[i + 1][j + 1].rgbtGreen;
                }
            }

            final_valueRed = (int) round(sqrt(pow(GxRed, 2) + pow(GyRed, 2)));
            final_valueBlue = (int) round(sqrt(pow(GxBlue, 2) + pow(GyBlue, 2)));
            final_valueGreen = (int) round(sqrt(pow(GxGreen, 2) + pow(GyGreen, 2)));

            // copies blurred to paste into the image once all final values for pixels are
            // calculated
            if (final_valueRed > 255)
            {
                copy[i][j].rgbtRed = 255;
            }
            else
            {
                copy[i][j].rgbtRed = final_valueRed;
            }

            if (final_valueBlue > 255)
            {
                copy[i][j].rgbtBlue = 255;
            }
            else
            {
                copy[i][j].rgbtBlue = final_valueBlue;
            }

            if (final_valueGreen > 255)
            {
                copy[i][j].rgbtGreen = 255;
            }
            else
            {
                copy[i][j].rgbtGreen = final_valueGreen;
            }
        }
    }

    // pastes copies of blurred pixels into image
    for (int r = 0; r < height; r++)
    {
        for (int p = 0; p < width; p++)
        {
            image[r][p].rgbtRed = copy[r][p].rgbtRed;
            image[r][p].rgbtBlue = copy[r][p].rgbtBlue;
            image[r][p].rgbtGreen = copy[r][p].rgbtGreen;
        }
    }
    return;
}
