/*
	Name: recover.c
	Version: 1
	Date: 06/03/2020
	Author: Mubeen Padaniya
	Function:
	Takes files as input. Reads input file and checks for jpeg files. If jpeg files found, it recovers the data and writes it
	into new files for each jpg header.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2) { //checking for proper usage
    	printf("Incorrect usage. \nUsage: ./recover filename\n");
    	return 1;
    }
    long int c;
    char i = 0;
	FILE *fr = fopen(argv[1], "r");
	if (fr == NULL) { //checking if the file can be opened
		printf("File cannot be opened. Ensure if file exists in the directory or is accessible.\n");
		return 1;
	}
	bool jpg_exist = false;
	while (!feof(fr)) { //till the end of file
		//checking for the first jpeg header
		c=fgetc(fr);
		if(c == 255) {
		    c=fgetc(fr);
		    if (c == 216) {
		    	c=fgetc(fr);
		    	if (c == 255) {
		    		c=fgetc(fr);
		    		if (c >= 224 && c <= 239) {
		    			//first jpg header detected
		    			jpg_exist = true;
		    			while (!feof(fr)) { //till the end of file
		    				char name[15];
		    				snprintf(name, 15, "%0003.0f.jpg",(float)i);
		    				FILE *fw = fopen(name,"w");      //create a new jpeg file numerically named
		    				BYTE header[] = {0xFF, 0xD8, 0xFF,c};
		    				fwrite(header,1,3,fw);    //write the image header to the file
		    				bool jpeg = true;
		    				while(jpeg) { //till a new jpeg starts or EOF is true
		    					c=fgetc(fr);
		    					if (c == 255) {
		    						//check for new jpg header.
		    						c=fgetc(fr);
		    						if (c == 216) {
		    							c=fgetc(fr);
		    							if (c == 255) {
		    								c=fgetc(fr);
		    								if (c >= 224 && c <= 239) {
		    									jpeg = false;
		    								}
		    								else {
		    									BYTE write[4] = {255,216,255,c};
		    									fwrite(write,1,4,fw);
		    								}
		    							}
		    							else {
		    							BYTE write[3] = {255,216,c};
		    							fwrite(write,1,3,fw);
		    							}
		    						}
		    						else {
		    							BYTE write[2] = {255,c};
		    							fwrite(write,1,2,fw);
		    						}
		    					}
		    					else if (feof(fr)) { //if EOF (End of File) is reached
		    						jpeg = false;
		    					}
		    					else {
		    						//write data from raw file to the new image file
		    						BYTE write[1] = {c};
		    						fwrite(write,1,1,fw);
		    					}
		    			}
		    			fclose(fw);
		    			i++;
		    			}
		    		}
		    	}
		    }
		}
	}
	if (!jpg_exist) {
		printf("No image files found :-(\n");
	}
	fclose(fr);
	return 0;
}
