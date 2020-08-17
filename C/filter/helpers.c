#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < (height-1); i++) {
        for (int j = 0; j < (width-1); j++) {
            int average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/3;
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < (height-1); i++) {
        for (int j = 0; j < (width-1)/2; j++) {
            unsigned char red = *&image[i][j].rgbtRed;
            unsigned char blue = *&image[i][j].rgbtBlue;
            unsigned char green = *&image[i][j].rgbtGreen;
            unsigned char red2 = *&image[i][width-j-1].rgbtRed;
            unsigned char blue2 = *&image[i][width-j-1].rgbtBlue;
            unsigned char green2 = *&image[i][width-j-1].rgbtGreen;
            image[i][j].rgbtRed = red2;
            image[i][j].rgbtBlue = blue2;
            image[i][j].rgbtGreen = green2;
            image[i][width-j-1].rgbtRed = red;
            image[i][width-j-1].rgbtBlue = blue;
            image[i][width-j-1].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height-1; i++) {
        for (int j = 0; j < width-1; j++) {
            if (i == 0 && j == 0) { //top left corner
                int avgRed = (image[i][j+1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed)/3;
                int avgBlue = (image[i][j+1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue)/3;
                int avgGreen = (image[i][j+1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen)/3;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (i == 0 && j == width-1) { //top right corner
                int avgRed = (image[i][j-1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j-1].rgbtRed)/3;
                int avgBlue = (image[i][j-1].rgbtBlue+image[i-1][j].rgbtBlue+image[i+1][j-1].rgbtBlue)/3;
                int avgGreen = (image[i][j-1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j-1].rgbtGreen)/3;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (i == height-1 && j == 0) { //bottom left corner
                int avgRed = (image[i][j+1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed)/3;
                int avgBlue = (image[i][j+1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue)/3;
                int avgGreen = (image[i][j+1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen)/3;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (i == height-1 && j == width-1) { //bottom right corner
                int avgRed = (image[i-1][j].rgbtRed+image[i][j-1].rgbtRed+image[i-1][j-1].rgbtRed)/3;
                int avgBlue = (image[i-1][j].rgbtBlue+image[i][j-1].rgbtBlue+image[i-1][j-1].rgbtBlue)/3;
                int avgGreen = (image[i-1][j].rgbtGreen+image[i][j-1].rgbtGreen+image[i-1][j-1].rgbtGreen)/3;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (i == 0 && j != 0 && j != width-1) { //top side
                int avgRed = (image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j-1].rgbtRed+image[i][j-1].rgbtRed)/5;
                int avgBlue = (image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i][j-1].rgbtBlue)/5;
                int avgGreen = (image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i][j-1].rgbtGreen)/5;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (i == height-1 && j != 0 && j != width-1) { //bottom side
                int avgRed = (image[i][j+1].rgbtRed+image[i-1][j+1].rgbtRed+image[i-1][j].rgbtRed+image[i-1][j-1].rgbtRed+image[i][j-1].rgbtRed)/5;
                int avgBlue = (image[i][j+1].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i-1][j].rgbtBlue+image[i-1][j-1].rgbtBlue+image[i][j-1].rgbtBlue)/5;
                int avgGreen = (image[i][j+1].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i-1][j].rgbtGreen+image[i-1][j-1].rgbtGreen+image[i][j-1].rgbtGreen)/5;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (j == 0 && i != 0 && i != height-1) { //left side
                int avgRed = (image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed+image[i+1][j].rgbtRed)/5;
                int avgBlue = (image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue+image[i+1][j].rgbtBlue)/5;
                int avgGreen = (image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen+image[i+1][j].rgbtGreen)/5;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else if (j == width-1 && i != 0 && i != height-1) {
                int avgRed = (image[i-1][j].rgbtRed+image[i-1][j-1].rgbtRed+image[i][j-1].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j].rgbtRed)/5;
                int avgBlue = (image[i-1][j].rgbtBlue+image[i-1][j-1].rgbtBlue+image[i][j-1].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j].rgbtBlue)/5;
                int avgGreen = (image[i-1][j].rgbtGreen+image[i-1][j-1].rgbtGreen+image[i][j-1].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j].rgbtGreen)/5;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
            else {
                int avgRed = (image[i-1][j].rgbtRed+image[i-1][j+1].rgbtRed+image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed+image[i+1][j].rgbtRed+image[i+1][j-1].rgbtRed+image[i][j-1].rgbtRed+image[i-1][j-1].rgbtRed)/8;
                int avgBlue = (image[i-1][j].rgbtBlue+image[i-1][j+1].rgbtBlue+image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue+image[i+1][j].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i][j-1].rgbtBlue+image[i-1][j-1].rgbtBlue)/8;
                int avgGreen = (image[i-1][j].rgbtGreen+image[i-1][j+1].rgbtGreen+image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen+image[i+1][j].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i][j-1].rgbtGreen+image[i-1][j-1].rgbtGreen)/8;
                image[i][j].rgbtRed = avgRed;
                image[i][j].rgbtBlue = avgBlue;
                image[i][j].rgbtGreen = avgGreen;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
     for(int i = 0; i < height-1; i++) {
        for (int j = 0; j < width-1; j++) {
            if (i == 0 && j == 0) { //top left corner
                long int GxR = 2*image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed;
                long int GxB = 2*image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue;
                long int GxG = 2*image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen;
                long int GyR = 2*image[i+1][j].rgbtRed+image[i+1][j+1].rgbtRed;
                long int GyB = 2*image[i+1][j].rgbtBlue+image[i+1][j+1].rgbtBlue;
                long int GyG = 2*image[i+1][j].rgbtGreen+image[i+1][j+1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (i == 0 && j == width-1) { //top right corner
                long int GxR = -2*image[i][j-1].rgbtRed-image[i+1][j-1].rgbtRed;
                long int GxB = -2*image[i][j-1].rgbtBlue-image[i+1][j-1].rgbtBlue;
                long int GxG = -2*image[i][j-1].rgbtGreen-image[i+1][j-1].rgbtGreen;
                long int GyR = 2*image[i+1][j].rgbtRed+image[i+1][j-1].rgbtRed;
                long int GyB = 2*image[i+1][j].rgbtBlue+image[i+1][j-1].rgbtBlue;
                long int GyG = 2*image[i+1][j].rgbtGreen+image[i+1][j-1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (i == height-1 && j == 0) { //bottom left corner
                long int GxR = 2*image[i][j+1].rgbtRed+image[i-1][j+1].rgbtRed;
                long int GxB = 2*image[i][j+1].rgbtBlue+image[i-1][j+1].rgbtBlue;
                long int GxG = 2*image[i][j+1].rgbtGreen+image[i-1][j+1].rgbtGreen;
                long int GyR = -2*image[i-1][j].rgbtRed-image[i-1][j+1].rgbtRed;
                long int GyB = -2*image[i-1][j].rgbtBlue-image[i-1][j+1].rgbtBlue;
                long int GyG = -2*image[i-1][j].rgbtGreen-image[i-1][j+1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (i == height-1 && j == width-1) { //bottom right corner
                long int GxR = -2*image[i][j-1].rgbtRed-image[i-1][j-1].rgbtRed;
                long int GxB = -2*image[i][j-1].rgbtBlue-image[i-1][j-1].rgbtBlue;
                long int GxG = -2*image[i][j-1].rgbtGreen-image[i-1][j-1].rgbtGreen;
                long int GyR = -2*image[i-1][j].rgbtRed-image[i-1][j-1].rgbtRed;
                long int GyB = -2*image[i-1][j].rgbtBlue-image[i-1][j-1].rgbtBlue;
                long int GyG = -2*image[i-1][j].rgbtGreen-image[i-1][j-1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (i == 0 && j != 0 && j != width-1) { //top side
                long int GxR = 2*(image[i][j+1].rgbtRed-image[i][j-1].rgbtRed)+(image[i+1][j+1].rgbtRed-image[i+1][j-1].rgbtRed);
                long int GxB = 2*(image[i][j+1].rgbtBlue-image[i][j-1].rgbtBlue)+(image[i+1][j+1].rgbtBlue-image[i+1][j-1].rgbtBlue);
                long int GxG = 2*(image[i][j+1].rgbtGreen-image[i][j-1].rgbtGreen)+(image[i+1][j+1].rgbtGreen-image[i+1][j-1].rgbtGreen);
                long int GyR = 2*image[i+1][j].rgbtRed+image[i+1][j-1].rgbtRed+image[i+1][j+1].rgbtRed;
                long int GyB = 2*image[i+1][j].rgbtBlue+image[i+1][j-1].rgbtBlue+image[i+1][j+1].rgbtBlue;
                long int GyG = 2*image[i+1][j].rgbtGreen+image[i+1][j-1].rgbtGreen+image[i+1][j+1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (i == height-1 && j != 0 && j != width-1) { //bottom side
                long int GxR = 2*(image[i][j+1].rgbtRed-image[i][j-1].rgbtRed)+(image[i-1][j+1].rgbtRed-image[i-1][j-1].rgbtRed);
                long int GxB = 2*(image[i][j+1].rgbtBlue-image[i][j-1].rgbtBlue)+(image[i-1][j+1].rgbtBlue-image[i-1][j-1].rgbtBlue);
                long int GxG = 2*(image[i][j+1].rgbtGreen-image[i][j-1].rgbtGreen)+(image[i-1][j+1].rgbtGreen-image[i-1][j-1].rgbtGreen);
                long int GyR = -2*image[i-1][j].rgbtRed-image[i-1][j-1].rgbtRed-image[i-1][j+1].rgbtRed;
                long int GyB = -2*image[i-1][j].rgbtBlue-image[i-1][j-1].rgbtBlue-image[i-1][j+1].rgbtBlue;
                long int GyG = -2*image[i-1][j].rgbtGreen-image[i-1][j-1].rgbtGreen-image[i-1][j+1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (j == 0 && i != 0 && i != height-1) { //left side
                long int GxR = 2*image[i][j+1].rgbtRed+image[i+1][j+1].rgbtRed+image[i-1][j+1].rgbtRed;
                long int GxB = 2*image[i][j+1].rgbtBlue+image[i+1][j+1].rgbtBlue+image[i-1][j+1].rgbtBlue;
                long int GxG = 2*image[i][j+1].rgbtGreen+image[i+1][j+1].rgbtGreen+image[i-1][j+1].rgbtGreen;
                long int GyR = 2*(image[i+1][j].rgbtRed-image[i-1][j].rgbtRed)+(image[i+1][j+1].rgbtRed-image[i-1][j+1].rgbtRed);
                long int GyB = 2*(image[i+1][j].rgbtBlue-image[i-1][j].rgbtBlue)+(image[i+1][j+1].rgbtBlue-image[i-1][j+1].rgbtBlue);
                long int GyG = 2*(image[i+1][j].rgbtGreen-image[i-1][j].rgbtGreen)+(image[i+1][j+1].rgbtGreen-image[i-1][j+1].rgbtGreen);
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else if (j == width-1 && i != 0 && i != height-1) { //right side
                long int GxR = -2*image[i][j-1].rgbtRed-image[i+1][j-1].rgbtRed-image[i-1][j-1].rgbtRed;
                long int GxB = -2*image[i][j-1].rgbtBlue-image[i+1][j-1].rgbtBlue-image[i-1][j-1].rgbtBlue;
                long int GxG = -2*image[i][j-1].rgbtGreen-image[i+1][j-1].rgbtGreen-image[i-1][j-1].rgbtGreen;
                long int GyR = 2*(image[i+1][j].rgbtRed-image[i-1][j].rgbtRed)+(image[i+1][j-1].rgbtRed-image[i-1][j-1].rgbtRed);
                long int GyB = 2*(image[i+1][j].rgbtBlue-image[i-1][j].rgbtBlue)+(image[i+1][j-1].rgbtBlue-image[i-1][j-1].rgbtBlue);
                long int GyG = 2*(image[i+1][j].rgbtGreen-image[i-1][j].rgbtGreen)+(image[i+1][j-1].rgbtGreen-image[i-1][j-1].rgbtGreen);
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
            else {
                long int GxR = 2*(image[i][j+1].rgbtRed-image[i][j-1].rgbtRed)+image[i+1][j+1].rgbtRed+image[i-1][j+1].rgbtRed-image[i+1][j-1].rgbtRed-image[i-1][j-1].rgbtRed;
                long int GxB = 2*(image[i][j+1].rgbtBlue-image[i][j-1].rgbtBlue)+image[i+1][j+1].rgbtBlue+image[i-1][j+1].rgbtBlue-image[i+1][j-1].rgbtBlue-image[i-1][j-1].rgbtBlue;
                long int GxG = 2*(image[i][j+1].rgbtGreen-image[i][j-1].rgbtGreen)+image[i+1][j+1].rgbtGreen+image[i-1][j+1].rgbtGreen-image[i+1][j-1].rgbtGreen-image[i-1][j-1].rgbtGreen;
                long int GyR = 2*(image[i+1][j].rgbtRed-image[i-1][j].rgbtRed)+image[i+1][j+1].rgbtRed+image[i+1][j-1].rgbtRed-image[i-1][j+1].rgbtRed-image[i-1][j-1].rgbtRed;
                long int GyB = 2*(image[i+1][j].rgbtBlue-image[i-1][j].rgbtBlue)+image[i+1][j+1].rgbtBlue+image[i+1][j-1].rgbtBlue-image[i-1][j+1].rgbtBlue-image[i-1][j-1].rgbtBlue;
                long int GyG = 2*(image[i+1][j].rgbtGreen-image[i-1][j].rgbtGreen)+image[i+1][j+1].rgbtGreen+image[i+1][j-1].rgbtGreen-image[i-1][j+1].rgbtGreen-image[i-1][j-1].rgbtGreen;
                if (sqrt((GxR^2)+(GyR^2)) > 255) {
                    temp[i][j].rgbtRed = 255;
                }
                else if (sqrt((GxR^2)+(GyR^2)) <= 255) {
                    temp[i][j].rgbtRed = round(4*sqrt((GxR^2)+(GyR^2)));
                }
                if (sqrt((GxB^2)+(GyB^2)) > 255) {
                    temp[i][j].rgbtBlue = 255;
                }
                else if (sqrt((GxB^2)+(GyB^2)) <= 255) {
                    temp[i][j].rgbtBlue = round(4*sqrt((GxB^2)+(GyB^2)));
                }
                if (sqrt((GxG^2)+(GyG^2)) > 255) {
                    temp[i][j].rgbtGreen = 255;
                }
                else if (sqrt((GxG^2)+(GyG^2)) <= 255) {
                    temp[i][j].rgbtGreen = round(4*sqrt((GxG^2)+(GyG^2)));
                }
            }
        }
    }
    for (int i = 0; i < height-1; i++) {
        for (int j = 0; j < width-1; j++) {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}
