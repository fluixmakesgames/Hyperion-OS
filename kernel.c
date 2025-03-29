#include "./include/print.h"
#include "src/port.h"
#include "src/gdt.h"
#include "src/idt.h"



char *layout_US[] = {
	"!", "1","2","3","4","5","6","7","8","9","0","-","=","\b",
	"","q","w","e","r","t","y","u","i","o","p","[","]", "\n",
	"~","a","s","d","f","g","h","j","k","l",";","'","`",
	"{",":","z","x","c","v","b","n","m","}"
};

char getkey() {
	uint8_t scan = inb(0x60);
}

void kernel_main() {
   	// Simple usage of print_msg() to print a string to the screen
   	clear_screen();
   	print_msg("Initing GDT\n");
	gdtinit();
	print_msg("Initing IDT\n");
	idtinit();
	const char msg[] = "hello, syscall!\n";
	print_msg("Goodbye, world!\n");
}
