/*
 * Serial library
 * ser.h
 * https://github.com/hberg539/avr-gcc-libs
 */

#define SER_BAUDRATE 19200
#define SER_UBRR (((F_CPU / (SER_BAUDRATE * 16UL))) - 1)

void ser_init();
void ser_set_stdout();
void ser_set_stdin();
void ser_write(uint8_t data);
uint8_t ser_read();