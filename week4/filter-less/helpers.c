#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            // Get average
            int average = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0 );

            // Update pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            // ALgorithm provided
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            // Update pixel
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width / 2; j++){

            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;

        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // create and copy to a new image
    RGBTRIPLE copy[height][width];

    // loop through each pixel
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){

            // Initializing
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            int count = 0;

            // get neigbouring pixels
            for(int row = i - 1; row < i + 2; row++){
                for(int col = j - 1; col < j + 2; col++){
                    if(row >= 0 && row < height && col >= 0 && col < width){
                        sumRed += image[row][col].rgbtRed;
                        sumGreen += image[row][col].rgbtGreen;
                        sumBlue += image[row][col].rgbtBlue;
                        count++;
                    }
                }
            }

            // compute average and store to copy
            copy[i][j].rgbtRed = round(sumRed / (float) count);
            copy[i][j].rgbtGreen = round(sumGreen / (float) count);
            copy[i][j].rgbtBlue = round(sumBlue / (float) count);
        }
    }

    // copy back to image
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            image[i][j] = copy[i][j];
        }
    }
    return;
}
