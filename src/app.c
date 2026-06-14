
#include "app.h"
#include "shared-vars.h"

void app_start(void)
{
	// Vars:
	FILE* appstate_fp = fopen(CONFIG_DIR APPSTATE_FILE, "rb");
	
	// Fetch last Appstate if exists:
	if (appstate_fp)
	{
		if (fread(&Appstate, 1, sizeof(Appstate), appstate_fp) != sizeof(Appstate))
		{
			defaultize_appstate();
			fputs("\nWARNING: Seems "CONFIG_DIR APPSTATE_FILE" is corrupted. Using default Appstate", log_fp);
		}
		else
		{
			fclose(appstate_fp);
			fputs("\nDEBUG: Got "CONFIG_DIR APPSTATE_FILE" .Restoring Appstate.", log_fp);
		}
	}
	else 
	{
		defaultize_appstate();
		fputs("\nDEBUG: Seems this is a first-time run of the App. Using default Appstate.", log_fp);
	}
	
	// MYSELF: 	Now Appstate is set. From now on is in the hands of UI Dev with Appstate
	//			modification and drawing UI with it .
}



void defaultize_appstate(void)
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
	Appstate.volume = 40;
}

void app_quit(void)
{
	// Save current Appstate:
	if (FILE *fp = fopen(CONFIG_DIR APPSTATE_FILE, "wb"))
	{
		fwrite(&Appstate, sizeof(Appstate), 1, fp);
		fputs("\nDEBUG: Wrote Current Appstate to "CONFIG_DIR APPSTATE_FILE".", log_fp);
	}
	else
	{
		fprintf(log_fp, "\nfopen '"CONFIG_DIR APPSTATE_FILE"': %s", strerror(errno));
	}
}











