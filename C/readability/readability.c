/*
    Name: readability.c
    Description: Gets text input from user and outputs the readability according to Coleman-Liau index equivalent to U.S Grade Level.
    Author: Mubeen Padaniya
    Date: 5/1/2020
    Version: 1
*/
//required libraries
#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void) {
    int l_sum = 0;
    int w_sum = 1;
    int s_sum = 0;          //initializing variables for letter sum, word sum and sentence sum
    string s = get_string("Text: ");        //gets user input for text
    int txtlnth = strlen(s);                //calculates the length of input string
    for (int i = 0; i < txtlnth; i++) {
        if ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122)) {    //if binary value equal to ASCII values of A-Z and a-z
        //append the letter sum
            l_sum++;
        }
        else if (s[i] == 32) { //checks for spaces
        //appends the word sum. Starts from 1 as the last word doesnt have any spaces after it.
            w_sum++;
        }
        else if (s[i] == 46 || s[i] == 33 || s[i] == 63) {  //checks for !, . and ?
        //appends the sentence summ.
            s_sum++;
        }
    }
    float L = ((float)l_sum/w_sum)*100;         //letters per 100 words
    float S = ((float)s_sum/w_sum)*100;         //sentences per 100 words
    float index = 0.0588 * L - 0.296 * S - 15.8;//calculates the Coleman Liau index
    if (index >= 16) {              //for index >= 16th grade
        printf("Grade 16+\n");
    }
    else if (index < 1) {           //for index < 1st grade
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n", (int) round(index));  //for other grades, presents the rounded value
    }
}