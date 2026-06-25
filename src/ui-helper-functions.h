#ifndef UI_HELPER_FUNCTIONS_H
#define UI_HELPER_FUNCTIONS_H

#include "common.h"

// All the functions listed here are Made by Core Dev expeciting UI dev to use them as per needed.
// If UI Can directly call these functions, then a lot of overhead can be reduced from 
// core calling the function , managing it and sharing the functionality or result with UI .

//IMPORTANT: This header may have POSIX / Linux specifc functions . Windows support would be added in coming versions :)

files_list* list_files(char *path);
void free_filenames(files_list *filenames);
// files_list* list_playlists(char *playlist_name);
//		For list_playlists(), list_files() is enough. Playlists refer to texts file stored in PLAYLIST_DIR
//		which contain all the file paths for musics in that playlist on each line. 
//		These are not binary written and rather are just plain ASCII text of file paths seperated by newline.
// create a playlist: Also used to delete all content of the playlist. ie empty the playlist.
BOOL create_playlist(char* playlist_name); // Return True on success.
// This can also be used to create a playlist:
BOOL add_to_playlist(char* playlist_name, char* file_path);

#endif

//EXAMPLES:

// 1. list_files() and free_filenames()
/*
	files_list* filenames = list_files("/");
	if (!filenames) 
	{
		fputs("\nERROR FILENAMES", log_fp);
		return 1;
	}
	SHORT_UINT i = 0;
	fputs("\nfilenames:", log_fp);
	while (filenames[i].filename)
	{
		// do stuff
		fprintf(log_fp, "\n%s \t-> %d", filenames[i].filename, filenames[i].filetype);
		i++;
	}
	free_filenames(filenames);
*/


// 2. create_playlist() and add_to_playlist()
/* 
	create_playlist("english");
	add_to_playlist("english", "/home/user/spotui/test-music/Rick Astley - Never Gonna Give You Up.mp3");
*/
