
#ifndef UI_H
#define UI_H

#include "states.h"
#include <ncurses.h> 

void ui_init(void);
void ui_shutdown(void);

void ui_draw(const App_state *state, int key_pressed);

void ui_draw_main(const App_state *state, int key_pressed);
void drawTab_Library(WINDOW* win,int key_pressed);
void drawTab_Playlist(WINDOW* win,int key_pressed);
void drawTab_Search(WINDOW* win,int key_pressed);


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

typedef struct{
	unsigned int rows, cols;
	float scaleX, scaleY;
	unsigned int posX,posY,padX,padY,boxW,boxH;
} GRID_LAYOUT;

typedef struct{
	unsigned int selected,index;
} USER_CARD_STATE;



void grid_layout_init( GRID_LAYOUT* layout, WINDOW* win, int rows, int cols, float scaleY, float scaleX);
void drawCard(WINDOW* win, GRID_LAYOUT* layout, int row, int col, int color,char* text);

void keyHandler_Card(USER_CARD_STATE* User_Card_State,GRID_LAYOUT* Card,int n_total,int key_pressed);


#endif

