
#include "ui-helper-functions.h"


//IMPORTANT: The following function returns a pointer to heap meaning UI DEV MUST FREE IT ! Don't Forget to free pls.
//			 Use the given free_filenames() to free the obtained list.
//NOTE: I am Not listing hidden files. Request of such a functionality along with it's need if you want.
//NOTE: The following function does not Do any logging.
//NOTE: NULL in the list of files marks end of the list, ie no more files found.
// NOTE: Check files_list type from common.h
// Returns NULL on Failure/Error .
files_list* list_files(char *path)
{
	DIR *dir;
	files_list *filenames;
	void *filename;
	struct dirent *entry;
	unsigned i = 0;
	unsigned max_i = 29;
	
	if (!(dir = opendir(path)))
		return NULL;
	if (!(filenames = malloc(sizeof(files_list) * 30))) 
		return NULL;
	
	while((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue;	// prevent resulting hidden files.
		
		SHORT_UINT j=0;
		// Try malloc multiple times until succeeds.
		while (!(filename = malloc(strlen(entry->d_name) + 1)) && (j<3))
		{
			j++;
			if (j >= 3) 
				return NULL;
				// Tried malloc 3 times ,yet failed. 
		}
		strcpy(filename, entry->d_name);
		(filenames[i]).filetype = entry->d_type;
		(filenames[i]).filename = filename;
		
		i++;
		
		//realloc filenames if needed:
		if (i >= max_i)
		{
			void *temp;
			j=0;
			// Try realloc for 3 times before failing
			do {
				temp = realloc(filenames, ((max_i += 30) * sizeof(files_list)));
				j++;
				if (j >= 3) 
					return NULL;
			}
			while(!temp && j < 3);
			filenames = temp;
		}
	}
	(filenames[i]).filename = NULL; // Used to mark No more files in the given path , ie. end of 'filenames'
	
	return filenames;
}


void free_filenames(files_list *filenames)
{
	int i=0 ;
	while (!(filenames[i]).filename)
		free((filenames[i]).filename);
	free(filenames);	
}













