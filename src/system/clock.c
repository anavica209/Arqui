#include "../include/clock.h"

/**
 * Initializes the clock
 */
void initialize_clock(){
    _CLOCKS = 0;
    _MS_PER_CLOCK = 55;
}

/**
 * Handles the Timer Clock Interrupt
 */
void interrupt_08_handler(){
    _CLOCKS++;
}

