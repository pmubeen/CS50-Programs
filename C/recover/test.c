#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int counter;
		BYTE *ptr_d;
		FILE *ptr_fp;

		if((ptr_fp = fopen(argv[1], "rb"))==NULL)
		{
			printf("Unable to open the file!\n");
			exit(1);
		}else printf("Opened file successfully for reading.\n");

		fseek(ptr_fp,0,SEEK_END);
		long int f_size = (ftell(ptr_fp))/512;
		rewind(ptr_fp);

		ptr_d = (BYTE *)malloc(f_size*sizeof(BYTE));
		if(!ptr_d)
		{
			printf("Memory allocation error!\n");
			exit(1);
		}else printf("Memory allocation successful.\n");

		if(fread(ptr_d, 512*sizeof(BYTE), (f_size*sizeof(BYTE)), ptr_fp) == 0)
		{
			printf( "Read error!\n" );
			exit( 1 );
		}else printf( "Read was successful.\n" );
		fclose(ptr_fp);
		free(ptr_d);
		return 0;
}
