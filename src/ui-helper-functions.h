#ifndef UI_HELPER_FUNCTIONS_H
#define UI_HELPER_FUNCTIONS_H

#include "common.h"

// All the functions listed here are Made by Core Dev expeciting UI dev to use them as per needed.
// If UI Can directly call these functions, then a lot of overhead can be reduced from 
// core calling the function , managing it and sharing the functionality or result with UI .

//IMPORTANT: This header may have POSIX / Linux specifc functions . Windows support would be added in coming versions :)

void** list_files(char *path);
void free_filenames(char **filenames);



#endif

//EXAMPLES:

// 1. list_files() and free_filenames()
/*
	char** filenames = list_files("/home/user/Music/english");
	SHORT_UINT i = 0;
	fputs("\nfilenames:", log_fp);
	while (filenames[i])
	{
		// do stuff
		i++;
	}
	free_filenames(filenames);
*/
