
#include "common.h"

#ifndef APP_H
#define APP_H

void restore_states(void);
void save_states(void);

BOOL restore_state(FILE *fp, void *state_ptr, MAGIC_INT state);		//Returns True on success

void defaultize_appstate(void);
void defaultize_optionstate(void);
void defaultize_mainstate(void);
void defaultize_musicstate(void);
#endif

