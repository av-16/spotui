
#include "ui-helper-functions.h"


//IMPORTANT: The following function returns a pointer to heap meaning UI DEV MUST FREE IT ! Don't Forget to free pls.
//			 Use the given free_filenames() to free the obtained list.
//NOTE: I am Not listing hidden files. Request of such a functionality along with it's need if you want.
//NOTE: The following function does not Do any logging.
//NOTE: NULL in the list of files marks end of the list, ie no more files found.
// Returns NULL on Failure/Error .
void** list_files(char *path)
{
	DIR *dir;
	void **filenames;
	void *filename;
	struct dirent *entry;
	unsigned i = 0;
	unsigned max_i = 29;
	
	if (!(dir = opendir(path)))
		return NULL;
	if (!(filenames = malloc(sizeof(void*) * 30))) 
		return NULL;
	
	while((entry = readdir(dir)))
	{
		if (entry->d_name[0] == '.')
			continue;	// prevent outputting hidden files.
		
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
		filenames[i] = filename;
		
		i++;
		
		//realloc filenames if needed:
		if (i >= max_i)
		{
			void *temp;
			j=0;
			// Try realloc for 3 times before failing
			do {
				temp = realloc(filenames, ((max_i += 30) * sizeof(void*)));
				j++;
				if (j >= 3) 
					return NULL;
			}
			while(!temp && j < 3);
			filenames = temp;
		}
	}
	filenames[i] = NULL; // Used to mark No more files in the given path , ie. end of 'filenames'
	
	return filenames;
}


void free_filenames(char **filenames)
{
	int i=0 ;
	while (!filenames[i])
		free(filenames[i]);
	free(filenames);
		
}


// We can later add another parameter to insert musics in the same call when we create playlist
BOOL create_playlist(char* playlist_name)
{
	char *playlist = malloc(strlen(playlist_name) + strlen(PLAYLIST_DIR) + 1);
	if (!playlist) 
		return False;
	sprintf(playlist, PLAYLIST_DIR"%s", playlist_name);
	FILE *fp = fopen(playlist, "w");
	if (!fp)
		return False;
		
	
	free(playlist);
	fclose(fp);
	return True;
}


// Add a single music to the playlist. file_path of form $PATH+$FILENAME
// Functions doesn't validate if file_path exists. 
BOOL add_to_playlist(char* playlist_name, char* file_path)
{
	char *playlist = malloc(strlen(playlist_name) + strlen(PLAYLIST_DIR) + 1);
	if (!playlist) 
		return False;
	sprintf(playlist, PLAYLIST_DIR"%s", playlist_name);
	FILE *fp = fopen(playlist, "a");
	if (!fp)
		return False;
	free(playlist);
	
	fprintf(fp, "%s\n", file_path);
	fclose(fp);
	return True;
}








