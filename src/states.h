
#ifndef STATES_H
#define STATES_H ""

#include "common.h"

typedef struct 
{
	BOOL running;
	MAGIC_INT mode;
	MAGIC_INT tab;
	
	char* filename_curr;		// currently playing
	char* filename_next;		// next to play
	char* filename_prev;		// previously played
	BOOL playing;
	TIME_SECONDS time_elapsed;
	TIME_SECONDS time_duration;
	MAGIC_INT play_mode;
	BOOL track_mode;		// Playing a single track or a playlist. Need to be known to 
							// know what to display on 'Main' tab.
	SHORT_UINT volume;		// Expected to be b/w 0-100
} App_state;


typedef struct 
{
	MAGIC_INT option_hover;		// See which option is hovered (selected)
} Option_state;


typedef struct 
{
	char* filename_hover;	// File which is currently hovered/selected by the user. "Enter" makes it filename_curr
	char** playlist;		// UI Programmer must display each music from the playlist accordingly 
} Main_state;


typedef struct 
{
	char* filename;
	char* artist;
	char* album;
	char* lyrics;
	char* year;			// Year published
	char* metadata;		// Contain other metadata. Not necessary to use. This is just a placeholder. 
	
} Music_state;


// We don't need a Help_state because it's retrieved from a help file stored in the machine -
// Only the UI Part need to handle it. Main part doesn't know it even exists XD .




#endif 
