/*
 * mr_resetter.h
 *
 *  Created on: 6 Oct 2017
 *      Author: Amjad Y. Majid
 */

#ifndef INCLUDE_MR_RESETER_H_
#define INCLUDE_MR_RESETER_H_

extern unsigned __reset;

void mr_resetter();
void mr_resetter_confirm();
void mr_auto_reseter(unsigned int interval);
void mr_auto_rand_reseter(unsigned int interval);

#endif /* INCLUDE_MR_RESETER_H_ */
