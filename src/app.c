
#include "app.h"
#include "shared-vars.h"


//NOTES:
//	restore_$fns() return True if it restored the correct values into corresponding states. Check it
//	defaultize_fns() should do logginf of 'using defult $state'
//	Order of R/W States: Appstate, Optionstate, Mainstate, Musicstate


// Fetch all states defined in states.h ,if was saved previous sesssion into a bin file:
void restore_states(void)

{
	// Vars:
	FILE* fp = fopen(CONFIG_DIR STATES_FILE, "rb");
	
	// Order of reading is important. Check notes
	if (fp)
	{
		fputs("\nNOTE: Got "CONFIG_DIR STATES_FILE" .", log_fp);
		if (restore_state(fp, &Appstate, APPSTATE)){
			if (restore_state(fp, &Optionstate, OPTIONSTATE)){
				if (restore_state(fp, &Mainstate, MAINSTATE)){
					if (restore_state(fp, &Musicstate, MUSICSTATE)){
						//pass
						// everything was restored successfully
					}else{
						defaultize_musicstate();
					}
				}else{
					defaultize_musicstate();
					defaultize_mainstate();
				}
			}else{
				defaultize_mainstate();
				defaultize_musicstate();
				defaultize_optionstate();
			}
		}else{
			defaultize_appstate();
			defaultize_mainstate();
			defaultize_musicstate();
			defaultize_optionstate();
		}
		fclose(fp);
	}
	else 
	{
		fputs("\nNOTE: Seems this is a first-time run of the App. Using default States.", log_fp);
		
		defaultize_appstate();
		defaultize_optionstate();
		defaultize_mainstate();
		defaultize_musicstate();
	}
}


//Completed fn:
void save_states(void)
{
	FILE *fp = fopen(CONFIG_DIR STATES_FILE, "wb");
	// Save current Appstate:
<<<<<<< HEAD
=======
	FILE *fp = fopen(CONFIG_DIR STATES_FILE, "wb");
>>>>>>> core
	if (fp)
	{
		// Order of writing is important:
		fwrite(&Appstate, sizeof(Appstate), 1, fp);
		fwrite(&Optionstate, sizeof(Optionstate), 1, fp);
		fwrite(&Mainstate, sizeof(Mainstate), 1, fp);
		fwrite(&Musicstate, sizeof(Musicstate), 1, fp);
		
		fputs("\nNOTE: Wrote All Current States to "CONFIG_DIR STATES_FILE".", log_fp);
	}
	else
	{
		fprintf(log_fp, "\nfopen '"CONFIG_DIR STATES_FILE"': %s", strerror(errno));
	}
}

//Completed fn:
BOOL restore_state(FILE *fp, void *state_ptr, MAGIC_INT state)
{
	size_t state_size;
	char *state_name;
	// Determine state_size first:
	switch (state)
	{
		case APPSTATE:
			state_size = sizeof(Appstate);
			state_name = "Appstate";
			break;
		case OPTIONSTATE:
			state_size = sizeof(Optionstate);
			state_name = "Optionstate";
			break;
		case MAINSTATE:
			state_size = sizeof(Mainstate);
			state_name = "Mainstate";
			break;
		case MUSICSTATE:
			state_size = sizeof(Musicstate);
			state_name = "Musicstate";
			break;
		default:
			//No chance to get executed: 
			fputs(	"\nCRITICAL: Got an unknown state value in restore_state() in app.c. I Don't know how to read the FIle."\
					"This might probably be caused by a bug in code. Fix it eventhough I am defaultizing all remaining states."\
					, log_fp);
			return False;
	}
	
	
	if (fread(state_ptr, 1, state_size, fp) != state_size)
	{
		fputs("\nWARNING: Seems "CONFIG_DIR STATES_FILE" is corrupted.", log_fp);
		return False;
	}
	else
	{
		fprintf(log_fp, "\nNOTE: Restored %s.", state_name );
		return True;
	}
}


//Completed but Can be Modifyd:
void defaultize_appstate(void)
{
	//change later.
	Appstate.filename_curr = NULL;
	Appstate.filename_next = NULL;
	Appstate.filename_prev = NULL;
	Appstate.mode = OFFLINE_M;
	Appstate.play_mode = LOOP_M;
	
	Appstate.running = True;
	Appstate.playing = False;
	
	Appstate.tab = MAIN_M;
	Appstate.time_duration = 0;
	Appstate.time_elapsed = 0;
	Appstate.track_mode = True;
	Appstate.volume = 40;
	
	fputs("\nNOTE: Using default Appstate.", log_fp);
}


void defaultize_optionstate(void)
{
	Optionstate.option_hover = MAIN_M;
	fputs("\nNOTE: Using default Optionstate.", log_fp);
}


void defaultize_mainstate(void)
{
	Mainstate.filename_hover = NULL;
	fputs("\nNOTE: Using default Mainstate.", log_fp);
}


void defaultize_musicstate(void)
{
	Musicstate.filename = NULL;
	fputs("\nNOTE: Using default MusicState.", log_fp);
}








<<<<<<< HEAD


=======
>>>>>>> core
