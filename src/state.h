
#ifndef STATE_H
#define STATE_H

typedef struct {
    int counter;
    int running;
} AppState;

void state_init(AppState *state);

#endif

