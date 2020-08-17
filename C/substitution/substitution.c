/*
    Name: subsitution.c

    Description: Takes in a case sensitive 26 character alphabetical encryption key as an
    arguments to process substitution encryption and produce a reversible ciphertext.

    Author: Mubeen Padaniya
    Date: 5/1/2020
    Version 1
*/
#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[]) {

    string ABC = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //comparison string UPPERCASE
    string abc = "abcdefghijklmnopqrstuvwxyz"; //comparison string LOWERCASE
    string key = argv[1];                      //encryption key assigned to a string
    if (argc != 2) {        //if no input commands
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) {  //if less or more than 26 characters
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else {
        int key_lnth = strlen(key);     //length of the encryption key.
        for (int j = 0; j < strlen(key); j++) { //checking for duplication in the key
            for (int i = j+1; i < strlen(key); i++) {
                if (key[i] == key[j]) {
                    printf("Duplicate characters in the key! The characters in the key should be unique\n");
                    return 1;
                }
            }
            if (key[j] < 65 || (key[j] > 90 && key[j] < 97) || key[j] >122) {  //checking for invalid non alphabet characters
                printf("Invalid Characters");
                return 1;
            }
        }
        string plntxt = get_string("plaintext: "); //assigns user input for plaintext to string
        int pln_lnth = strlen(plntxt);             //plaintext string length
        string ciphtxt = plntxt;                   //ciphertext
        for (int i = 0; i <= pln_lnth; i++) {      //for all values of plaintext
            if (plntxt[i] >= 65 && plntxt[i] <= 90) { //1.check if its lowercase
                bool flag = true; // boolean for controlling bottom loop
                for (int j = 0; j <= key_lnth; j++) {   //for all values of ABC and key
                    if (ABC[j] == plntxt[i] && flag) {  //checking if ABC comparision string equals plaintext for a given character
                        if(key[j] >= 97) {              //if key is uppercase
                            ciphtxt[i] = key[j]-32;     //convert to key value in lowercase
                        }
                        else {
                            ciphtxt[i] = key[j];        //otherwise use key value as is
                        }
                        flag = false;                   //one loop per character
                    }
                }
            }
            else if (plntxt[i] >= 97 && plntxt[i] <= 122) { //2. check if plaintext character in UPPERCASE
                bool flag = true;  //boolean for controlling bottom loop
                for (int j = 0; j <= key_lnth; j++) { //for all values of abc and key
                    if(abc[j] == plntxt[i] && flag) { //checking if abc comparision string equals plaintext for a given character
                        if(key[j] < 97) {             //if key is in lowercase
                            ciphtxt[i] = key[j]+32;   //convert to key value in UPPERCASE
                        }
                        else {
                            ciphtxt[i] = key[j];      //otherwise use key value as is.
                        }
                        flag = false;                //one loop per character
                    }
                }
            }
        }
        printf("ciphertext: %s\n",ciphtxt);         //printsout the ciphertext
    }
}