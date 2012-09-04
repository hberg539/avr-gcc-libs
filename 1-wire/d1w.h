/*
 * Dallas/Maxim 1-Wire library
 * d1w.h
 * https://github.com/hberg539/avr-gcc-libs
 */

void d1w_init();
void d1w_write(uint8_t data);
uint8_t d1w_read();
