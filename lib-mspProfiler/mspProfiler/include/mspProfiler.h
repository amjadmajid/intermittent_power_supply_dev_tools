/*
 * codeProfiler.h
 *
 *  Created on: 27 Sep 2017
 *      Author: amjad
 */

#include "msp430.h"
#include "uart-debugger.h"
#include <stdint.h>

#ifndef INCLUDE_CODEPROFILER_H_
#define INCLUDE_CODEPROFILER_H_

#define  cp_reset()  TB0CTL |= TBCLR

void cp_init();
uint32_t cp_getRes();
void cp_sendRes(char * resId);

extern unsigned int __overflow;   // This must  be non-volatile

#endif /* INCLUDE_CODEPROFILER_H_ */
