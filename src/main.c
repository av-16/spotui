
#include "shared-vars.h"
#include "app.h"
#include "ui.h"
#include "states.h" //unnecessary
#include "common.h" //unnecessary

App_state Appstate;
Option_state Optionstate;
Main_state Mainstate;
Music_state Musicstate;
FILE* log_fp;

int main(void)
{   
	// Do Stuff to start logging:
	if (!(log_fp = fopen(CONFIG_DIR LOG_FILE, "a+")))
	{
		perror("fopen logfile");
		return 1;
	}
	
	// Do App init and restore Appstate:
	app_start();
	ui_init();
	
	// Main Loop:
	while (Appstate.running)
	{
		ui_draw(&Appstate);
	}
	
	// App was closed. We got stuff to do:
	app_quit();
	ui_shutdown();
	
	// Cleanup and stuff:
	fputs(LOG_DIVIDER, log_fp);
	fclose(log_fp);
	return 0;
}

