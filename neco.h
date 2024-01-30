#ifndef HEADER_FILE
#define HEADER_FILE

void serial_baudrate (unsigned long int new_baudrate);
int serial_init();
void serial_putc (unsigned char c);
void serial_puts (char *s);

#endif
