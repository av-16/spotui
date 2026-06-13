
#include <ncurses.h>
#include "ui.h"

void ui_init(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

void ui_shutdown(void)
{
    endwin();
}

void ui_draw(const AppState *state)
{
    erase();

    mvprintw(1, 2, "Simple TUI Example");
    mvprintw(3, 2, "Counter: %d", state->counter);

    mvprintw(5, 2, "UP    = increment");
    mvprintw(6, 2, "DOWN  = decrement");
    mvprintw(7, 2, "q     = quit");

    refresh();
}
