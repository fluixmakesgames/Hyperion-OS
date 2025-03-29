typedef struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t limit_middle;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
};

struct gdt_ptr {
	uint16_t limit;
	int base;
};


struct gdt_ptr gdtp;
int ecg = 0;

struct gdt_entry gdt[300];

int create_entry_gdt(uint16_t limit, int base, uint8_t access, uint8_t gran) {
	if(ecg < 300) {
		ecg++;
		gdt[ecg].limit_low = (limit & 0xFFFF);
		gdt[ecg].base_low = (base & 0xFFFF);
		gdt[ecg].base_middle = (base >> 16) & 0xFF;
		gdt[ecg].access = access;
		gdt[ecg].granularity = (limit >> 16) & 0x0F;
		gdt[ecg].granularity |= gran & 0xF0;
		gdt[ecg].base_high = (base >> 24) & 0xFF;
		return 0;
	} else {
		print_msg("Error: Too many entries in the GDT to create another entry!");
		return 1;
	}
}

void gdtinit() {
	gdtp.limit = sizeof(gdt) - 1;
	gdtp.base = (unsigned int)&gdt;
	create_entry_gdt(0, 0, 0, 0);
	create_entry_gdt(0xFF, 0, 0x92, 0xCF);
	create_entry_gdt(0xFF, 0, 0x9A, 0xCF);
	asm volatile("lgdt (%0)"
		:
		:"r"(&gdtp));
}
