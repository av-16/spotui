
#include <ncurses.h>

#include "app.h"
#include "ui.h"
#include "state.h"
#include "input.h"
#include <unistd.h>

void app_run(void)
{
    AppState state;

    state_init(&state);

    ui_init();

    while (state.running) {
        ui_draw(&state);
        sleep(0.5);

        int key = getch();

        handle_input(&state, key);
    }

    ui_shutdown();
}

