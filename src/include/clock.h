#ifndef __CLOCK_H__
#define __CLOCK_H__

int _CLOCKS;
int _MS_PER_CLOCK;

// Initializes the clock
void initialize_clock();

// Handles the Timer Clock Interrupt (IRQ 8)
void int_08();

// Increase or decrease the frequency
void speed_up_clock(int steps);

#endif // __CLOCK_H__
