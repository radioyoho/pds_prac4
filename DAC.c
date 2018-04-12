/*
 * DAC.c
 *
 *  Created on: Feb 26, 2018
 *      Author: aland
 */
#include "DAC.h"

#define LIMIT 0xFF
#define SHIFT 8

void DAC0_clockGating()
{
	///Configures clock gating with an or to not mess up everything else.
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
}

void DAC0_enable()
{
	///Enables DAC and sets reference voltage to ref1.
	DAC0->C0 |= (DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK);
}

void DAC0_newValue(uint16 newvalue)
{
	///Assings value to high and low register, taking into account that the high reg only has 4 bits.
	DAC0->DAT->DATL = newvalue & LIMIT;
	DAC0->DAT->DATH = newvalue >> SHIFT;
}
