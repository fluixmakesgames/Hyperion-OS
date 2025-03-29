struct idt_entry {
	uint16_t base_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t type_attr;
	uint16_t base_high;
};

struct idt_ptr {
	uint16_t limit;
	int base;
};

int icg = 0;

struct idt_entry idt[300];
struct idt_ptr idtp;

int div_zero() {
	print_msg("Error: Divide by 0!");
	while(1) {
		asm("hlt");
	}
}

struct interrupt_frame;

void syscall() {
	asm volatile("popa");
	int eax;
	int edx;
	asm volatile(
	"mov %%eax, %0\n"
	:"=r"(eax)
	:
	);
	asm volatile(
	"mov %%edx, %0\n"
	:"=r"(edx)
	:
	);
	if(eax == 1) {
		print_msg(edx);
	}
	asm volatile("pusha");
	asm volatile("iret");
}


int create_entry_idt(unsigned int base, uint16_t selector, uint8_t type_attr) {
        if(ecg < 300) {
                icg++;
		idt[icg].base_low = (base & 0xFFFF);
    		idt[icg].base_high = (base >> 16) & 0xFFFF;
    		idt[icg].selector = selector;
    		idt[icg].zero = 0;
		idt[icg].type_attr = type_attr;
                return 0;
        } else {
                print_msg("Error: Too many entries in the IDT to create another");
                return 1;
        }
}



void idtinit() {
	idtp.limit = sizeof(idt) - 1;
	idtp.base = (unsigned int)&idt;

	//Div by ZERO
	create_entry_idt((unsigned int)div_zero, 0x08, 0x8E);
	//Syscalls
	create_entry_idt((unsigned int)syscall, 0x08, 0x80);
	asm volatile("lidt (%0)"
                :
                :"r"(&gdtp));
}
