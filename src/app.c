
#include "app.h"
#include "shared-vars.h"

int app_start(void)
{
	//change later.
	Appstate.filename_curr = NULL;
	Appstate.filename_next = NULL;
	Appstate.filename_prev = NULL;
	Appstate.mode = OFFLINE_M;
	Appstate.play_mode = LOOP_M;
	
	Appstate.playing = True;
	Appstate.running = True;
	Appstate.playing = False;
	
	Appstate.tab = MAIN_M;
	Appstate.time_duration = 0;
	Appstate.time_elapsed = 0;
	Appstate.track_mode = True;
	Appstate.volume = 50; 
	
	
	
	return 1;
}


















