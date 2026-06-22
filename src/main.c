
#include "shared-vars.h"
#include "app.h"
#include "appstate-functions.h"
#include "ui-helper-functions.h"
#include "ui.h"

App_state Appstate;
Option_state Optionstate;
Main_state Mainstate;
Music_state Musicstate;

FILE* log_fp;
char key_press;

int main(void)
{   
	BOOL pressed_enter_key = False;
	
	// Do Stuff to start logging:
	if (!(log_fp = fopen(CONFIG_DIR LOG_FILE, "a+")))
	{
		perror("fopen logfile");
		return 1;
	}
	
	// Do App init and restore Appstate:
	restore_states();
	ui_init();

	// Main Loop:
	while (Appstate.running)
	{
		ui_draw(&Appstate);
		sleep(0.33);
		key_press = getchar();
		
		if (key_press=='q') break; // Change
		else if (key_press=='\n') pressed_enter_key = True;
		
		
		
		
		
		BOOL pressed_enter_key = False;
	}
	
	// App was closed. We got stuff to do:
	save_states();
	ui_shutdown();
	
	// Cleanup and stuff:
	fputs(LOG_DIVIDER, log_fp);
	fclose(log_fp);
	return 0;
}

