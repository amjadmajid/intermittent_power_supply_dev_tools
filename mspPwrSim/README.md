# Intermittent Power Simulation Library

With this library it is possible to simulate intermittent power on the TI MSP430. The built-in timer (TimerA0) is used for this purpose. Three modes with different period lengths are available to use at the same time:
1. on-line mode
2. sleep mode
3. off-line mode.

In on-line mode normal execution is simulated.
In sleep mode a low-power mode is simulated, where the node is sleeping and wating for an interrupt and therefore can use it's energy for a longer period.
In off-line mode the energy has been depleted and the node is charging (no execution possible).

## Usage
To start using the library the following commands needs to be used:
 `start_power_simulation(interval)`
, where `interval` is in microseconds (has to be corrected if using divider).
After the inter has passed the node will go to off-line mode.

It is also possible to switch from on-line mode to sleep mode using `switch_timer_to_long()` and back using `switch_timer_to_short()`. The remaining energy (time left) is then converted between the two modes.

The periods in sleep mode and off-line mode are always X times the on-line period. This is regulated using the following definitions:
```c
#define off_factor 9
#define sleep_factor 30
```
