#include "int.h"

static uint8_t inb(int port) {
	uint8_t val;
	asm volatile
	("inb %1, %0"
	:"=a" (val)
	:"d" (port)
	:"memory"
	);
	return val;
}

static uint8_t outb(int port, uint8_t data) {
	asm volatile
	("outb %0, %1"
	:
	:"a" (data), "d" (port)
	:"memory"
	);
}
