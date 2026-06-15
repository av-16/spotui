
// Here, we have all common types, enums and stuff.

#ifndef COMMON_H
#define COMMON_H ""

#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "config.h"

//START:

typedef unsigned TIME_SECONDS;	// Time in seconds. 32 bit holds upto 1193046 hours
									// 16 bit holds upto 18 hours. 8 bit holds upto 4.2 miniutes
typedef unsigned char SHORT_UINT;
typedef char SHORT_INT;

typedef enum {False = 0, True = 1} BOOL; 

// MAGIC_INT is a short int type which represents 
// each unique integer as serving a special purpose
// Magic Ints: All magic ints end with '_M'	:
typedef enum 
{
	// mode:
	OFFLINE_M,
	ONLINE_M,
	
	// menu:
	OPTIONS_M,
	HELP_M,
	MAIN_M,
	MUSIC_M,
	
	// play_mode:
	SHUFFLE_M,
	SEQUENCE_M,
	LOOP_M,
	
	// options:
	PLAY_FILE,
	PLAY_FOLDER,
	PLAY_PLAYLIST,
	ADD_PLAYLIST
	
} MAGIC_INT;
// No seperate tab for Online/Offline. It's like a toggle switch








#endif
