
#include "shared-vars.h"
#include "appstate-functions.h"

void process_appstate(void)
{
	switch (Appstate.tab)
	{
		case MAIN_M:
			process_main_m();
			break;
		case OPTIONS_M:
			process_options_m();
			break;
		case MUSIC_M:
			process_music_m();
			break;
		case HELP_M:
			// We don't have to do anything. UI dev does stuff.
			break;
		default: 
			// No way the following logging gets executed in any scenario. 
			fputs( "CRITICAL: Got something else for Appstate.tab. This was not possible "\
					"since Appstate.tab was of enum MAGIC_INT type", log_fp);
			break;
	}
}

void process_options_m(void)
{
	switch (Optionstate.option_hover)
	{
		case PLAY_FILE:
			//TODO
			break;
		case PLAY_FOLDER:
			//TODO
			break;
		case PLAY_PLAYLIST:
			//TODO
			break;
		case ADD_PLAYLIST:
			//TODO
			break;
		default:
			// No way the following logging gets executed in any scenario. 
			fputs( "CRITICAL: Got something else for Optionstate.option_hover. This was not possible "\
					"since Optionstate.option_hover was of enum MAGIC_INT type", log_fp);
			break;
	}
}


void process_main_m(void)
{
	//TODO
}


void process_music_m(void)
{
	//TODO
}
