/*******************************************************************************
* 
* FILENAME : utils.h
*
* DESCRIPTION : Header file containing general utility functions
*
* AUTHOR : filipang 
* 
* START DATE :		5/11/2021
*
*******************************************************************************/

#ifndef UTILS_H 
#define UTILS_H

#define KIB(a) (a*1024)
#define MIB(a) (a*1024*1024)
#define GIB(a) (a*1024*1024*1024)

#define struct_offset(s, att) ((void*)(&((struct s *)NULL)->att)) 

#define PI 3.14159265359

void utilsLoadFile(const char* file_name, char *dest, int *size);
void utilsLoadFileNullTerminated(const char* file_name, char *dest, int *size);
void utilsWriteFile(const char* file_name, unsigned char *data, int data_size);

#endif
