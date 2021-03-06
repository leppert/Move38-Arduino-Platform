/*
 * ir_comms.h
 *
 * All the functions for communication and waking on the 6 IR LEDs on the tile edges.
 *
 */ 

#ifndef IR_H_
#define IR_H_

#include "blinkcore.h"

#define IRLED_COUNT FACE_COUNT

#define ALL_IR_BITS (0b00111111)        // All six IR LEDs

// Setup pins, interrupts

void ir_init(void);

// Enable IR normal operation (call after init or disable)

// TODO: Specify specific LEDs?

void ir_enable(void);

// Stop IR interrupts (call after enable)

void ir_disable(void);

// TODO: Queue TX so they only happen after a successful RX or idle time. Unnecessary since TX time so short?

// Send a series of pulses with spacing_ticks clock ticks between each pulse (or as quickly as possible if spacing too short)
// If count=0 then 256 pulses will be sent.
// If spaceing_ticks==0, then the time between pulses will be 65536 ticks

// bit 0= led IR0 , bit 1= led IR1...

// This clobbers whatever charge was on the selected LEDs, so only call after you have checked it.
// TODO: Fix this. Save previous charge state

void ir_tx_pulses(uint8_t count, uint16_t spacing_ticks , uint8_t bitmask);

// Measure the IR LEDs to to see if they have been triggered.
// Returns a 1 in each bit for each LED that was fired.
// Fired LEDs are recharged.

uint8_t ir_test_and_charge( void );


// Called anytime on of the IR LEDs triggers, which could
// happen because it received a flash or just because
// enough ambient light accumulated

void __attribute__((weak)) ir_callback(uint8_t triggered_bits);


#define WAKEON_IR_BITMASK_NONE     0             // Don't wake on any IR change
#define WAKEON_IR_BITMASK_ALL      IR_BITS       // Don't wake on any IR change

#endif /* IR_H_ */