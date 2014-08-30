#ifndef TIMER_H
#define TIMER_H

#include <sys/types.h>

uint32_t timer_get_ticks();

void timer_set_ticks(uint32_t init_ticks);

void init_timer(uint32_t frequency);

void sleep(uint32_t secs);

#endif
