typedef struct gdt_entry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t limit_middle;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr {
	uint16_t limit;
	int base;
} __attribute__((packed));


struct gdt_ptr gdtp;


struct gdt_entry gdt[30] = {
    	{0, 0, 0, 0, 0, 0},
    	{0xFF00, 0, 0, 0x9A, 0xCF, 0},
    	{0xFF00, 0xFF01, 0, 0x92, 0xCF, 0}
	};

void gdtinit() {
	gdtp.limit = sizeof(gdt) - 1;
	print_msg("FAILED TO INIT GDT (ERROR: FUNCTION NOT FINISHED)\n");
}
