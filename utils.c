/*******************************************************************************
* 
* FILENAME : utils.c
*
* DESCRIPTION : Source file containing general utility functions
*
* AUTHOR : filipang 
* 
* START DATE :		5/11/2021
*
*******************************************************************************/

// NOTE(filip): Don't define DEBUG when releasing
#define DEBUG

// NOTE(filip): Consider moving these defines in include files that use them
#define ASSERT(a) if(!(a)) *((unsigned int*)0) = 0xDEAD; 

// Loads entire file into a char*
void utilsLoadFile(const char* file_name, char *dest, int *size)
{
//	char *dest = NULL;
	FILE *fp = fopen(file_name, "r");
	if (fp != NULL) {
		// Go to the end of the file. 
		if (fseek(fp, 0L, SEEK_END) == 0) {
			// Get the size of the file. 
			long bufsize = ftell(fp);
			if (bufsize == -1) {   }

			// Allocate our buffer to that size. 
			//dest = malloc(sizeof(char) * (bufsize + 1));
			*size = sizeof(char) * (bufsize);

			// Go back to the start of the file. 
			if (fseek(fp, 0L, SEEK_SET) != 0) { }

			//Read the entire file into memory. 
			size_t newLen = fread(dest, sizeof(char), bufsize, fp);
			if ( ferror( fp ) != 0 ) {
				fputs("Error reading file", stderr);
			}
		}
		fclose(fp);
	}
}

// Loads entire file into a char* 
void utilsLoadFileNullTerminated(const char* file_name, char *dest, int *size)
{
//	char *dest = NULL;
	FILE *fp = fopen(file_name, "r");
	if (fp != NULL) {
		// Go to the end of the file. 
		if (fseek(fp, 0L, SEEK_END) == 0) {
			// Get the size of the file. 
			long bufsize = ftell(fp);
			if (bufsize == -1) {   }

			// Allocate our buffer to that size. 
			//dest = malloc(sizeof(char) * (bufsize + 1));
			*size = sizeof(char) * (bufsize + 1);

			// Go back to the start of the file. 
			if (fseek(fp, 0L, SEEK_SET) != 0) { }

			//Read the entire file into memory. 
			size_t newLen = fread(dest, sizeof(char), bufsize, fp);
			if ( ferror( fp ) != 0 ) {
				fputs("Error reading file", stderr);
			} else {
				dest[newLen++] = '\0'; // Just to be safe. 
			}
		}
		fclose(fp);
	}
}

void utilsWriteFile(const char* file_name, unsigned char *data, int data_size)
{
	FILE *fp = fopen(file_name, "w");
	if (fp != NULL) 
	{
		//Read the entire file into memory. 
		size_t newLen = fwrite(data, sizeof(char), data_size, fp);
		if ( ferror( fp ) != 0 ) 
		{
			fputs("Error reading file", stderr);
		} 
		fclose(fp);
	}
	else
	{
		printf("Can't open file!\n");
	}
}

