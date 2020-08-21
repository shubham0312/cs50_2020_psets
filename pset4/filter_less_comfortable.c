#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (image[i][j].rgbtBlue == image[i][j].rgbtGreen && image[i][j].rgbtBlue == image[i][j].rgbtRed)
            {
                continue;
            }
            else
            {
                double average;
                int new_pixel;
                average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
                new_pixel = round(average);
                if (new_pixel > 255)
                {
                    new_pixel = 255;
                }
                image[i][j].rgbtBlue = new_pixel;
                image[i][j].rgbtGreen = new_pixel;
                image[i][j].rgbtRed = new_pixel;

            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    double Red, Green, Blue;
    int sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Red = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            Green = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            Blue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            sepiaRed = round(Red);
            sepiaGreen = round(Green);
            sepiaBlue = round(Blue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)
    {
        int val = width / 2;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < val; j++)
            {
                int temp1, temp2, temp3;
                temp1 = image[i][j].rgbtRed;
                temp2 = image[i][j].rgbtGreen;
                temp3 = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtRed = temp1;
                image[i][width - j - 1].rgbtGreen = temp2;
                image[i][width - j - 1].rgbtBlue = temp3;
            }

        }
    }
    else
    {
        int val = (width - 1) / 2;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < val; j++)
            {
                int temp1,temp2,temp3;
                temp1 = image[i][j].rgbtRed;
                temp2 = image[i][j].rgbtGreen;
                temp3 = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
                image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
                image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
                image[i][width - j - 1].rgbtRed = temp1;
                image[i][width - j - 1].rgbtGreen = temp2;
                image[i][width - j - 1].rgbtBlue = temp3;
            }

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double Red = 0.0, Blue = 0.0, Green = 0.0;
    int blurRed = 0, blurBlue = 0, blurGreen = 0;  //NOTE : firstly we will have to store all the values of image in a new array. Because if we do not do that then the original image values will be altered while finding and storing the averages.
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
               if (j == 0)
               {
                  Red = (image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0;
                  Green = (image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0;
                  Blue = (image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0;
               }
               else if (j == width - 1)
               {
                   Red = (image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed) / 4.0;
                   Green = (image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 4.0;
                   Blue = (image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 4.0;
               }
               else 
               {
                   Red = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed) / 6.0;
                   Green = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen) / 6.0;
                   Blue = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue) / 6.0;
               }
            }   
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    Red = (image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i][j].rgbtRed) / 4.0;
                    Green = (image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j].rgbtGreen) / 4.0;
                    Blue = (image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j].rgbtBlue) / 4.0;
                }
                else if (j == width - 1)
                {
                    Red = (image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed) / 4.0;
                    Green = (image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen) / 4.0;
                    Blue = (image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue) / 4.0;
                }
                else
                {
                    Red = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0;
                    Green = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0;
                    Blue = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0;
                }
                
            }
            else if (j == 0 && i != height - 1 && i != 0)
            {
                Red = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0;
                Green = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0;
                Blue = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0;
            }
            else if (j == width - 1 && i != height - 1 && i != 0)
            {
                Red = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0;
                Green = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0;
                Blue = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0;
            }
            else
            {
                Red = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0;
                Green = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0;
                Blue = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0;
                
            }
            

            blurRed = round(Red);
            blurGreen = round(Green);
            blurBlue = round(Blue);
            if (blurRed > 255)
            {
                blurRed = 255;

            }
            if (blurGreen > 255)
            {
                blurGreen = 255;

            }
            if (blurBlue > 255)
            {
                blurBlue = 255;

            }

            new_image[i][j].rgbtRed = blurRed;
            new_image[i][j].rgbtBlue = blurBlue;
            new_image[i][j].rgbtGreen = blurGreen;

        }
    }
    for (int l = 0; l < height; l++)
    {
        for (int m = 0; m < width; m++)
        {
            image[l][m].rgbtRed = new_image[l][m].rgbtRed;
            image[l][m].rgbtGreen = new_image[l][m].rgbtGreen;
            image[l][m].rgbtBlue = new_image[l][m].rgbtBlue;
        }
    }
    return;
}
