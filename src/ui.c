
#include "ui.h"
#include "ui-helper-functions.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h" 


////GLOBAL VARIABLES

// ramps: dark->bright
static const char *RAMP = ".'`^\",:;Il!i~+_-?][}{1)(|\\/*tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
TAB currentTab = LIBRARY;

//files_list* filenames;

BOOL GREYSCALE  = FALSE;

float scaleX = .97; // can be modified
float scaleY = .99; // can be modified

WINDOW * winMain;
WINDOW * winMain_menu;

GRID_LAYOUT Card_Library;
GRID_LAYOUT Card_Playlist;

USER_CARD_STATE User_Card_State_Library;
USER_CARD_STATE User_Card_State_Playlist;

void ui_init(void)
{

//	filenames =  list_files("/home/kite/Videos/");
//	while (filenames[n_files].filename){
//		n_files++;
//	}

	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
//	nodelay(stdscr, TRUE);
//	set_escdelay(25); 
	curs_set(0);

	//Checking if terminal has colors. BUT there is no greyscale mode.. for now; Have to make it later.
        if (!has_colors()) {
		GREYSCALE = True;
		int i = 0;
		erase();
		mvprintw(3, 2, "WARNING!!");
		mvprintw(5, 2, "Your Terminal has no colors!!");
		mvprintw(6, 2, "Switching ASCII art to GREYSCALE");
		refresh();
		while (i<3){
			i += 1;
			sleep(1);
		}
		erase();
		refresh();
	}
	start_color();
	use_default_colors();

	int ROWS,COLS;
	getmaxyx(stdscr,ROWS,COLS);	
	winMain = newwin(ROWS*scaleY,COLS*scaleX,(ROWS*(1.0-scaleY))/2,(COLS*(1.0-scaleX))/2);

	// Spotui - title
	box(winMain,0,0);
	mvwprintw(winMain,0, 2, "Spotui");
	
	//Colors
	short nc[] = {
	    COLOR_RED, COLOR_GREEN, COLOR_YELLOW, COLOR_BLUE,
	    COLOR_MAGENTA, COLOR_CYAN, COLOR_WHITE, COLOR_BLACK
	};
	for (int i = 0; i < 8; i++) {
	    init_pair(i+1, nc[i], -1); // bg default
	}

	// MAIN MENU
	int rows,cols;	
	getmaxyx(winMain,rows,cols);	
	winMain_menu = newwin(rows - 4,cols - 4, (ROWS-rows)/2+2,(COLS-cols)/2+2);
	box(winMain_menu,0,0);

	grid_layout_init( &Card_Library, winMain_menu, 3, 3, .8, .8);
	grid_layout_init( &Card_Playlist, winMain_menu, 3, 1, .8, .8);
}

void ui_shutdown(void)
{
	delwin(winMain);
	delwin(winMain_menu);
	endwin();
//	free_filenames(filenames);
}

// Draws the UI based on the app state
void ui_draw(const App_state *state, int key_pressed)
{
	wrefresh(winMain);

	switch (state->mode) {
	        case MAIN_M:
	        	ui_draw_main(state,key_pressed);
	                break;
// Only made menu

//		case OPTIONS_M:
//	        	ui_draw_options(state,key_pressed);
//	                break;
//		case HELP_M:
//	        	ui_draw_help(state,key_pressed);
//	                break;
//		case MUSIC_M: 
//	        	ui_draw_music(state,key_pressed);
//	                break;
        	default:
	        	ui_draw_main(state,key_pressed);
		        break; 
	}	
}

// Draws content in Menu based on the currentTab
void ui_draw_main(const App_state *state, int key_pressed)
{
	werase(winMain_menu);

	box(winMain_menu,0,0);
	mvwprintw(winMain_menu,0, 2, "Library");
	mvwprintw(winMain_menu,0, 10, "Playlist");
	mvwprintw(winMain_menu,0, 19, "Search");

	// change tab on key press
	switch (key_pressed){
		case 'l':
			currentTab = LIBRARY;	
			break;
		case 'p':
			currentTab = PLAYLIST;	
			break;
		case 's':
			currentTab = SEARCH;	
			break;
		default:
			break;
	}
	
	// highlight current tabname
	switch (currentTab){
		case LIBRARY:
			wattron(winMain_menu,A_STANDOUT);
			mvwprintw(winMain_menu,0, 2, "Library");
			wattroff(winMain_menu,A_STANDOUT);
			drawTab_Library(winMain_menu,key_pressed);
			break;
		case PLAYLIST:
			wattron(winMain_menu,A_STANDOUT);
			mvwprintw(winMain_menu,0, 10, "Playlist");
			wattroff(winMain_menu,A_STANDOUT);
			drawTab_Playlist(winMain_menu,key_pressed);
			break;
		case SEARCH:
			wattron(winMain_menu,A_STANDOUT);
			mvwprintw(winMain_menu,0, 19, "Search");
			wattroff(winMain_menu,A_STANDOUT);
			drawTab_Search(winMain_menu,key_pressed);
			break;
		default:
			break;
	}

	wrefresh(winMain_menu);
}

// Draws the Tab LIBRARY in the winMain_menu
void drawTab_Library(WINDOW* win,int key_pressed){
	// This gets replaced with list of songs
	char *songs[] = {"Song1","Song2","Song3","Song4","Song5","Song6","Song7","Song8","Song9","Song10"};

	int rows = Card_Library.rows;
        int cols = Card_Library.cols;
	// This gets replaced with total no. of songs
	int n_total = 10;

	wrefresh(win);
 
	int color;
	
	// Draws the card
	// The card - small boxes that can be controlled with arrow keys and contains name of the song.
	for ( int r = 0; r < rows; r++ ){

		// checks if row is needed or not
		// r*cols is no. of items/songs displayed till now
		if (User_Card_State_Library.index+1 + r*cols > n_total){
			break;
		}

		for ( int c = 0; c < cols; c++ ){
			// checks if column is needed or not
			// r*cols + c is the no. of items/songs displayed till now
			if (User_Card_State_Library.index+1 + r*cols+c > n_total){
				break;
			}


			if (User_Card_State_Library.selected == User_Card_State_Library.index+r*cols+c){
				 color = 1;
			}
			else{
				color = 7;
			}
			
			drawCard(win, &Card_Library, r, c, color, songs[User_Card_State_Library.index+r*cols+c]);

		}
	}
	
	// Updates index and selected as key presses
	keyHandler_Card(&User_Card_State_Library,&Card_Library,n_total,key_pressed);

}


void drawTab_Playlist(WINDOW* win,int key_pressed){
	char *playlists[] = {"Playlist1","Playlist2","Playlist3","Playlist4"};

	int n_total = 4;
	int rows = Card_Playlist.rows;
	int cols = Card_Playlist.cols;
	wrefresh(win);
	
        int color;
	// Draws the card
	// The card - small boxes that can be controlled with arrow keys and contains name of the song.
	for ( int r = 0; r < rows; r++ ){

		// checks if row is needed or not
		// r*cols is no. of items/songs displayed till now
		if (User_Card_State_Playlist.index+1 + r*cols > n_total){
			break;
		}

		for ( int c = 0; c < cols; c++ ){
			// checks if column is needed or not
			// r*cols + c is the no. of items/songs displayed till now
			if (User_Card_State_Playlist.index+1 + r*cols+c > n_total){
				break;
			}

	
			if (User_Card_State_Playlist.selected == User_Card_State_Playlist.index+r*cols+c){
				 color = 1;
			}
			else{
				color = 7;
			}
			
			drawCard(win, &Card_Playlist, r, c, color, playlists[User_Card_State_Playlist.index+r*cols+c]);



		}
	}
	
	// Updates index and selected as key presses
	keyHandler_Card(&User_Card_State_Playlist,&Card_Playlist,n_total,key_pressed);

}

void drawTab_Search(WINDOW* win,int key_pressed){
	int winH,winW;
	getmaxyx(win,winH,winW);	
	
	winH -= 2;
	winW -= 2;
	
	char* image = "./rick3.jpeg";

	dispay_Image(win,winH,winW,image);
}

// Handles the input in selection of card
void keyHandler_Card(USER_CARD_STATE* User_Card_State,GRID_LAYOUT* Card,int n_total,int key_pressed){
	int rows = Card->rows;
        int cols = Card->cols;

	switch (key_pressed){

		case KEY_UP:
			if (User_Card_State->selected - cols < User_Card_State->index) {
				if (User_Card_State->index - cols >= 0){
					User_Card_State->index -= cols;	
					User_Card_State->selected -= cols;
				}
			}
			else if (User_Card_State->selected > cols){
				User_Card_State->selected -= cols;
			}
			break;
		case KEY_DOWN:
			if (User_Card_State->selected + cols  >= User_Card_State->index + cols*rows) {
				if (User_Card_State->selected + cols <= n_total - 1 )
					User_Card_State->selected += cols;
				if (User_Card_State->index + cols*rows + 1 <= n_total )
					User_Card_State->index += cols;	
				
			}
			else{
				if (User_Card_State->selected + cols < n_total)
				User_Card_State->selected += cols;
			}

			break;
		case KEY_LEFT:
			if ( User_Card_State->selected  > 0 ){
				User_Card_State->selected -= 1;
				if ( User_Card_State->selected < User_Card_State->index)
					User_Card_State->index -= cols;
			}
			break;
		case KEY_RIGHT:
			if ( User_Card_State->selected +1 < n_total ){
				User_Card_State->selected += 1;
				if ( User_Card_State->index + cols*rows <= User_Card_State->selected )
					User_Card_State->index += cols;
			}
			break;
		default:
			break;
	}
}

void grid_layout_init( GRID_LAYOUT* layout, WINDOW* win, int rows, int cols, float scaleY, float scaleX){
	int winH,winW;
	getmaxyx(win,winH,winW);	
	winH -= 2;
	winW -= 2;
	int x,y;
	getbegyx(win, y, x);

	float padX = (winW * (1 - scaleX))/(cols+1);
	float padY = (winH * (1 - scaleY))/(rows+1);
	float boxW = (winW * scaleX)/cols;
	float boxH = (winH * scaleY)/rows;

	*layout = (GRID_LAYOUT){
		.rows = rows,
		.cols = cols,	
		.scaleY = scaleY,
		.scaleX = scaleX,
	        .posX = x,
	        .posY = y,
		.padX = padX,
		.padY = padY,
		.boxW = boxW,
		.boxH = boxH
        
	};


} 

// Draws a card
void drawCard(WINDOW* win, GRID_LAYOUT* layout, int row, int col, int color,char* text) 
{

	if ( col > layout->cols || row > layout->rows ) return;

	WINDOW* card= newwin(	layout->boxH,
				layout->boxW,
				layout->posY+1+(row+1)*layout->padY+row*layout->boxH, 
				layout->posX+1+(col+1)*layout->padX+col*layout->boxW);
	werase(card);
	wattron(card,COLOR_PAIR(color));

	box(card,0,0);
	mvwprintw(card,1,1,"%s", text); // Write name

	wattroff(card,COLOR_PAIR(color));
	wrefresh(card);
	delwin(card);

}



// might be useful in future.. but for now useless.
void draw_rect_border(WINDOW* win, int y, int x, int h, int w) {
    if (h < 2 || w < 2) return;

    // corners
    mvwaddch(win, y,     x,     ACS_ULCORNER);
    mvwaddch(win, y,     x+w-1, ACS_URCORNER);
    mvwaddch(win, y+h-1, x,     ACS_LLCORNER);
    mvwaddch(win, y+h-1, x+w-1, ACS_LRCORNER);

    // top/bottom
    for (int i = 1; i < w-1; i++) {
        mvwaddch(win, y,     x+i, ACS_HLINE);
        mvwaddch(win, y+h-1, x+i, ACS_HLINE);
    }

    // left/right
    for (int i = 1; i < h-1; i++) {
        mvwaddch(win, y+i, x,     ACS_VLINE);
        mvwaddch(win, y+i, x+w-1, ACS_VLINE);
    }
}

//display image
int dispay_Image(WINDOW* win,int winH,int winW,char* image ) {

	int sw, sh, ch;
	unsigned char *rgb = stbi_load(image, &sw, &sh, &ch, 3); // force RGB
	if (!rgb) {
		werase(win);
		printf("\n\n");
		fprintf(stderr, "Failed to load image: %s\n",image); 
		return 1; 
	}

	int imgH = winH - 2;
	int imgW = winW - 2;

	double aspect = (double)sh / (double)sw;
	int drawW = imgW;
	int drawH = (int)(aspect * drawW);
	if (drawH > imgH) {
	    drawH = imgH;
    	drawW = (int)(drawH / aspect);
	}
	int offX = (winW - drawW*2) / 2;
	int offY = (winH - drawH) / 2;
	int rampLen = (int)strlen(RAMP) - 1;

	for (int y = 0; y < drawH; y++) {
		int sy = (int)((long long)y * sh / drawH);
		if (sy >= sh) sy = sh - 1;

		int shift = 0;

		for (int x = 0; x < drawW; x++) {
            		int sx = (int)((long long)x * sw / drawW);
            		if (sx >= sw) sx = sw - 1;

            		int i = (sy * sw + sx) * 3;
            		int r = rgb[i+0], g = rgb[i+1], b = rgb[i+2];

            // brightness for ASCII
	            	int br = (int)(0.299*r + 0.587*g + 0.114*b); // 0..255
            		char ch = RAMP[(br * rampLen) / 255];

            // simple color selection (retro): decide a palette index by which channel dominates
            		int idx = 1;
            		if (r >= g && r >= b) idx = 1;          // red
            		else if (g >= r && g >= b) idx = 2;     // green
            		else if (b >= r && b >= g) idx = 4;     // blue

            // make it feel more “vivid”: boost yellows/cyans when two channels are strong
            		if (r > 160 && g > 160) idx = 3;        // yellow
            		if (g > 160 && b > 160) idx = 6;        // cyan
            		if (r > 160 && b > 160) idx = 5;        // magenta

            // dim pixels to black/white to pop outlines
            		if (br < 40) idx = 8;                  // black
            		else if (br > 220) idx = 7;           // white
			int wy = 1 + offY + y;
	        	int wx = 1 + offX+ x + shift;
            		wattron(win,COLOR_PAIR(idx));
            		mvwaddch(win,wy,wx, ch);
            		wattroff(win,COLOR_PAIR(idx));

			shift += 1;
        	}
   	}
	stbi_image_free(rgb);
	return 0;
}


