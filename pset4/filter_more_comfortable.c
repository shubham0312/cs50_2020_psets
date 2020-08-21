#include "helpers.h"
#include <math.h>
#include <cs50.h>
 // firstly read the problem statement
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) 
{ //Here we will try to make the image grayscale. 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {   // if the value of the red green blue pixels of the image are equal then just leave that pixel as it is and move forward
            if (image[i][j].rgbtBlue == image[i][j].rgbtGreen && image[i][j].rgbtBlue == image[i][j].rgbtRed) 
            {
                continue;
            }
            else // if the value of the red green blue color pixels  are not equal then find the average of them   
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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    if (width % 2 == 0)  //if the width of the image is even
    {
        int val = width / 2;
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < val; j++)  
            // swaping the image pixels
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
    else  // if the width is odd 
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

bool valid_pixel(int i, int j, int height, int width)  // this function is created to check if the pixel which is selected is valid or not 
{
    if(i >= 0 && i < height && j >= 0 && j < width)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int cap(int val) //function to check the value of the pixel range is between 0 to 255.
{
    return (val <= 255? val: 255);
}

RGBTRIPLE edges_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};  // initializing the value of Gx and Gy matrix
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int redValueX = 0, greenValueX = 0, blueValueX = 0;
    int redValueY = 0, greenValueY = 0, blueValueY = 0;
    for (int di = -1; di <= 1; di++)  // starting a loop to find the 3 X 3 
    {
        for (int dj = -1; dj <= 1; dj++)
        {
            if(valid_pixel(i + di, j + dj, height, width)) // now checking if the selected pixel is valid 
            {
                int weightX = Gx[di + 1][dj + 1];
                redValueX += weightX * image[i + di][j + dj].rgbtRed;
                greenValueX += weightX * image[i + di][j + dj].rgbtGreen;
                blueValueX += weightX * image[i + di][j + dj].rgbtBlue;
                
                int weightY = Gy[di + 1][dj + 1];
                redValueY += weightY * image[i + di][j + dj].rgbtRed;
                greenValueY += weightY * image[i + di][j + dj].rgbtGreen;
                blueValueY += weightY * image[i + di][j + dj].rgbtBlue;
            }
        }
    }
    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round(sqrt(redValueX * redValueX + redValueY * redValueY)));
    pixel.rgbtGreen = cap(round(sqrt(greenValueX * greenValueX + greenValueY * greenValueY)));
    pixel.rgbtBlue = cap(round(sqrt(blueValueX * blueValueX + blueValueY * blueValueY)));
    return pixel;
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = edges_pixel(i, j, height, width, image);
        }
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = new_image[i][j].rgbtRed;
            image[i][j].rgbtGreen = new_image[i][j].rgbtGreen;
            image[i][j].rgbtBlue = new_image[i][j].rgbtBlue;
        }
    }
    return;
}
