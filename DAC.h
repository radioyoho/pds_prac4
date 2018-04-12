/*
 * DAC.h
 *
 *  Created on: Feb 26, 2018
 *      Author: aland
 */

#ifndef DAC_H_
#define DAC_H_

#include "DataTypeDefinitions.h"
#include "PIT.h"
#include "MK64F12.h"

/**
 * 	\brief Enables clock gating for DAC.
 */

void DAC0_clockGating(void);

/**
 * 	\brief Necessary configurations to use DAC.
 */

void DAC0_enable(void);

/**
 * 	\brief Assigns new value to DAC.
 *
 * 	\input[in] newvalue 12 bit value for DAC.
 */

void DAC0_newValue(uint16 newvalue);

#endif /* PIT_H_ */
