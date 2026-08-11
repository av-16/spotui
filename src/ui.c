
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
			break;
		case SEARCH:
			wattron(winMain_menu,A_STANDOUT);
			mvwprintw(winMain_menu,0, 19, "Search");
			wattroff(winMain_menu,A_STANDOUT);
			break;
		default:
			break;
	}

	wrefresh(winMain_menu);
}

// this needs to be somewhere else
int selected = 0;
int index = 0;

// Draws the Tab LIBRARY in the winMain_menu
void drawTab_Library(WINDOW* win,int key_pressed){
	// This gets replaced with list of songs
	char *songs[] = {"Song1","Song2","Song3","Song4","Song5","Song6","Song7","Song8","Song9"};

	int rows = 3; // can be modified
	int cols = 3; // can be modified

	// So many variables are declared every frame which is inefficient.
	// plus they are not changing through out program as well
	// Have to optimise it later...

	int winH,winW;
	getmaxyx(win,winH,winW);	
	winH -= 2;
	winW -= 2;
	int x,y;
	getbegyx(win, y, x);

	float scaleX = .8; // can be modified	
	float scaleY = .8; // can be modified	

	float padX = (winW * (1 - scaleX))/(cols+1);
	float padY = (winH * (1 - scaleY))/(rows+1);
	float boxW = (winW * scaleX)/cols;
	float boxH = (winH * scaleY)/rows;

//	mvwprintw(win,10,9, "%d %d",winW,winH);
//	mvwprintw(win,11,9, "%f %f",boxW,boxH);
//	mvwprintw(win,1,0, "%d %d",KEY_DOWN,key_pressed);
//	int n_total = n_files-1;

	// This gets replaced with total no. of songs
	int n_total = 9;

	wrefresh(win);
	
	// Draws the card
	// The card - small boxes that can be controlled with arrow keys and contains name of the song.
	// The if conditions maybe difficult to read
	for ( int r = 0; r < rows; r++ ){

		// checks if row is needed or not
		// r*cols is no. of items/songs displayed till now
		if (index+1 + r*cols > n_total){
			break;
		}

		for ( int c = 0; c < cols; c++ ){
			// checks if column is needed or not
			// r*cols + c is the no. of items/songs displayed till now
			if (index+1 + r*cols+c > n_total){
				break;
			}

			// starting_y = y of winMain_menu(main box) + no. of rows till now * height of rows +
				// paddingY * (no. of rows till now + 1)
			// starting_x = x of winMain_menu(main box) + no. of columns till now * width of columns + 
				// paddingX * (no. of columns till now + 1)
			// Since the values are taken as int anyways there may be unequal padding or dimension due to
				// loss occured by conversion of float -> int 
			WINDOW* card= newwin(boxH,boxW,y+1+(r+1)*padY+r*boxH,x+1+(c+1)*padX+c*boxW);
			werase(card);
			if (selected == index+r*cols+c) wattron(card,COLOR_PAIR(1)); // currently red - can be changed 

			box(card,0,0);
			mvwprintw(card,1,1,"%s", songs[index+r*cols+c]); // Write song name
//			mvwprintw(card,1,1, filenames[index+r*cols+c].filename);

			if (selected == index+r*cols+c) wattroff(card,COLOR_PAIR(1)); // update value here also
			wrefresh(card);
			delwin(card);
		}
	}
	
	// Updates index and selected as key presses
	switch (key_pressed){

		case KEY_UP:
			if (selected - cols < index) {
				if (index - cols >= 0){
					index -= cols;	
					selected -= cols;
				}
			}
			else{
				selected -= cols;
			}
			break;
		case KEY_DOWN:
			if (selected + cols >= index + cols*rows) {
				if (index + cols*rows + cols < n_total){
					index += cols;	
					selected += cols;
				}
			}
			else{
				if (selected + cols < n_total)
				selected += cols;
			}
			break;
		case KEY_LEFT:
			if ( selected -1 >= 0 ){
				selected -= 1;
			}
			break;
		case KEY_RIGHT:
			if ( selected +1 < n_total ){
				selected += 1;
			}
			break;
		default:
			break;
	}
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

//display image - needs to be fixed 
int dispay_Image(WINDOW* win,int winH,int winW,char* image ) {

	int sw, sh, ch;
	unsigned char *rgb = stbi_load(image, &sw, &sh, &ch, 3); // force RGB
	if (!rgb) {
		fprintf(stderr, "Failed to load image\n"); 
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
	int offX = (imgW - drawW) / 2;
	int offY = (imgH - drawH) / 2;
	int rampLen = (int)strlen(RAMP) - 1;

	for (int y = 0; y < drawH; y++) {
		int sy = (int)((long long)y * sh / drawH);
		if (sy >= sh) sy = sh - 1;

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
	        	int wx = 1 + offX + x;
            		wattron(win,COLOR_PAIR(idx));
            		mvwaddch(win,wy,wx, ch);
            		wattroff(win,COLOR_PAIR(idx));
        	}
   	}
	stbi_image_free(rgb);
	return 0;
}


