/*
 * mspPwrSim.h
 *
 * previously mr_resetter.h
 *
 *  Created on: 6 Oct 2017
 *      Author: Amjad Y. Majid
 *
 *  Modified on: 23 Jan 2019
 *           by: Patrick Schilder
 *
 * modification: Added off-time (charging time) and switch to low power mode
 *
 */

void start_power_simulation(unsigned int interval);
void switch_timer_to_short();
void switch_timer_to_long();
