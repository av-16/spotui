
#ifndef UI_H
#define UI_H

#include "states.h"
#include <ncurses.h> 

void ui_init(void);
void ui_shutdown(void);

void ui_draw(const App_state *state, int key_pressed);

void ui_draw_main(const App_state *state, int key_pressed);
void drawTab_Library(WINDOW* win,int key_pressed);

int dispay_Image(WINDOW* win,int winH,int winW,char* image ); 
void draw_rect_border(WINDOW* win, int y, int x, int h, int w);


// Represents Tabs
// Currently contains tabs from main menu only
typedef enum 
{
	LIBRARY,
	PLAYLIST,
	SEARCH

} TAB;


#endif

