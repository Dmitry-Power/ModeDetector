#ifndef LPC2148_UART_REGS
#define LPC2148_UART_REGS

volatile unsigned char* const UART_LC_REG[] = {(volatile unsigned char*) 0xE000C00C, (volatile unsigned char*) 0xE001000C};
volatile unsigned char* const UART_DLL_REG[] = {(volatile unsigned char*) 0xE000C000, (volatile unsigned char*) 0xE0010000};
volatile unsigned long* const UART_IE_REG[] = {(volatile unsigned long*) 0xE000C004, (volatile unsigned long*) 0xE0010004};
volatile unsigned long* const UART_IID_REG[] = {(volatile unsigned long*) 0xE000C008, (volatile unsigned long*) 0xE0010008};
volatile unsigned char* const UART_BUFFERS_REG[] = {(volatile unsigned char*) 0xE000C000, (volatile unsigned char*) 0xE0010000};
volatile unsigned char* const UART_FDR_REG[] = {(volatile unsigned char*) 0xE000C028, (volatile unsigned char*) 0xE0010028};
volatile unsigned char* const UART_LSTAT_REG[] = {(volatile unsigned char*) 0xE000C014, (volatile unsigned char*) 0xE0010014};
volatile unsigned char* const UART_FCR_REG[] = {(volatile unsigned char*) 0xE000C008, (volatile unsigned char*) 0xE0010008};

#endif

