#include <ncurses.h>
#include "input.h"

void handle_input(AppState *state, int key)
{
    switch (key) {
    case KEY_UP:
        state->counter++;
        break;

    case KEY_DOWN:
        state->counter--;
        break;

    case 'q':
        state->running = 0;
        break;
    }
}
