#include "helpers.h"
#include <stdio.h>
#include <math.h>

int min(int, int);

//swap rgb byte values of pixels on two ends for reflection
void swap(BYTE *num1, BYTE *num2)
{
    BYTE temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //printf("%i : %i : %i ", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            int avg_rgb = (int) round(((float) image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            //printf("avg: %i\n", avg_rgb);

            image[i][j].rgbtBlue = avg_rgb;
            image[i][j].rgbtRed = avg_rgb;
            image[i][j].rgbtGreen = avg_rgb;

        }

        //printf("\n");


    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //printf("%i : %i : %i ", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            //int avg_rgb = (int) round ((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3);
            //printf("avg: %i\n", avg_rgb);

            float originalRed = image[i][j].rgbtRed;
            float originalGreen = image[i][j].rgbtGreen;
            float originalBlue = image[i][j].rgbtBlue;

            int sepiaRed = (int)(round)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = (int)(round)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = (int)(round)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            image[i][j].rgbtBlue = min(255, sepiaBlue);
            image[i][j].rgbtRed = min(255, sepiaRed);
            image[i][j].rgbtGreen = min(255, sepiaGreen);

        }

        //printf("\n");


    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid_index = 0;
    if (width % 2 == 0)
    {
        mid_index = width / 2;
    }
    else
    {
        mid_index = ceil((float) width / 2);
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid_index; j++)
        {
            //printf("Before %i : %i : %i ", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            //printf("Before %i : %i : %i \n", image[i][width-j-1].rgbtBlue, image[i][width-j-1].rgbtRed, image[i][width-j-1].rgbtGreen);


            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);

            //printf("After %i : %i : %i ", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            //printf("After %i : %i : %i\n", image[i][width-j-1].rgbtBlue, image[i][width-j-1].rgbtRed, image[i][width-j-1].rgbtGreen);

        }

        //printf("\n");


    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];

    // very lazy way of doing box blur - works for now
    // the checks can be designed better
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int avg_r = 0;
            int avg_g = 0;
            int avg_b = 0;

            int sum_r = 0;
            int sum_g = 0;
            int sum_b = 0;

            int count = 0;

            // if ( i == 1 && j == 1)
            // {
            //     //printf("Before %i : %i : %i ", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            //     avg_of_neighbors(i, j, height, width, image);
            //     //printf("After %i : %i : %i\n", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            // }

            //printf("\nCurrent ij: %i %i\n", i, j);

            // top row
            if (i > 0)
            {
                // i-1, j-1 top left
                if (j > 0)
                {
                    //printf("Added ij: %i %i\n", i-1, j-1);
                    sum_r +=  image[i - 1][j - 1].rgbtRed;
                    sum_g +=  image[i - 1][j - 1].rgbtGreen;
                    sum_b +=  image[i - 1][j - 1].rgbtBlue;
                    count++;
                    //printf("Add %i : %i : %i\n", image[i - 1][j - 1].rgbtBlue, image[i - 1][j - 1].rgbtRed, image[i - 1][j - 1].rgbtGreen);
                }

                // i-1, j top mid
                //printf("Added ij: %i %i\n", i-1, j);
                sum_r +=  image[i - 1][j].rgbtRed;
                sum_g +=  image[i - 1][j].rgbtGreen;
                sum_b +=  image[i - 1][j].rgbtBlue;
                count++;
                //printf("Add %i : %i : %i\n", image[i-1][j].rgbtBlue, image[i-1][j].rgbtRed, image[i-1][j].rgbtGreen);

                // i-1, j+1 top right
                if (j < width -1)
                {
                    //printf("Added ij: %i %i\n", i-1, j+1);
                    sum_r +=  image[i - 1][j + 1].rgbtRed;
                    sum_g +=  image[i - 1][j + 1].rgbtGreen;
                    sum_b +=  image[i - 1][j + 1].rgbtBlue;
                    count++;
                    //printf("Add %i : %i : %i\n", image[i - 1][j - 1].rgbtBlue,  image[i - 1][j + 1].rgbtRed,  image[i - 1][j + 1].rgbtGreen);
                }

            }

            // middle row
            // i, j-1 mid left
            if (j > 0)
            {
                //printf("Added ij: %i %i\n", i, j-1);
                sum_r +=  image[i][j - 1].rgbtRed;
                sum_g +=  image[i][j - 1].rgbtGreen;
                sum_b +=  image[i][j - 1].rgbtBlue;
                count++;
                //printf("Add %i : %i : %i\n", image[i][j - 1].rgbtBlue, image[i][j - 1].rgbtRed, image[i][j].rgbtGreen);
            }

            // i, j+1 mid right
            if (j < width - 1)
            {
                //printf("Added ij: %i %i\n", i, j+1);
                sum_r +=  image[i][j + 1].rgbtRed;
                sum_g +=  image[i][j + 1].rgbtGreen;
                sum_b +=  image[i][j + 1].rgbtBlue;
                count++;
                //printf("Add %i : %i : %i\n", image[i][j + 1].rgbtBlue, image[i][j + 1].rgbtRed, image[i][j + 1].rgbtGreen);
            }

            // bottom row
            if (i < height - 1)
            {
                // i+1, j-1 bottom left
                if (j > 0)
                {
                    //printf("Added ij: %i %i\n", i+1, j-1);
                    sum_r +=  image[i + 1][j - 1].rgbtRed;
                    sum_g +=  image[i + 1][j - 1].rgbtGreen;
                    sum_b +=  image[i + 1][j - 1].rgbtBlue;
                    count++;
                    //printf("Add %i : %i : %i\n", image[i + 1][j - 1].rgbtBlue, image[i + 1][j - 1].rgbtRed, image[i + 1][j - 1].rgbtGreen);
                }

                // i+1, j bottom mid
                //printf("Added ij: %i %i\n", i+1, j);
                sum_r +=  image[i + 1][j].rgbtRed;
                sum_g +=  image[i + 1][j].rgbtGreen;
                sum_b +=  image[i + 1][j].rgbtBlue;
                count++;
                //printf("Add %i : %i : %i\n", image[i + 1][j].rgbtBlue, image[i + 1][j].rgbtRed, image[i + 1][j].rgbtGreen);

                //i+1, j+1 bottom right
                if (j < width - 1)
                {
                    //printf("Added ij: %i %i\n", i+1, j+1);
                    sum_r +=  image[i + 1][j + 1].rgbtRed;
                    sum_g +=  image[i + 1][j + 1].rgbtGreen;
                    sum_b +=  image[i + 1][j + 1].rgbtBlue;
                    count++;
                    //printf("Add %i : %i : %i\n", image[i + 1][j + 1].rgbtBlue, image[i + 1][j + 1].rgbtRed, image[i + 1][j + 1].rgbtGreen);
                }


            }

            // self - i,j
            //printf("Added ij: %i %i\n", i, j);
            sum_r +=  image[i][j].rgbtRed;
            sum_g +=  image[i][j].rgbtGreen;
            sum_b +=  image[i][j].rgbtBlue;
            count++;
            //printf("Add %i : %i : %i\n", image[i][j].rgbtBlue, image[i][j].rgbtRed, image[i][j].rgbtGreen);
            //printf("count: %i\n", count);

            avg_r = (int) round((float) sum_r / count);
            avg_g = (int) round((float) sum_g / count);
            avg_b = (int) round((float) sum_b / count);

            new_image[i][j].rgbtBlue = avg_b;
            new_image[i][j].rgbtRed = avg_r;
            new_image[i][j].rgbtGreen = avg_g;


        }

        //printf("\n");
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}

//Find minimum between two numbers.
int min(int num1, int num2)
{
    return (num1 > num2) ? num2 : num1;
}
