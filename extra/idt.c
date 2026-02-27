// Interrupt Descriptor Table

/***********************************************************/
// System includes

#include <stdint.h>

/***********************************************************/
// Structs

// Structure representing the bytes of an idt gate.
typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

// Register defns.
typedef struct {
    // data segment selector
    uint32_t ds;
    // general purpose registers pushed by pusha
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    // pushed by isr procedure
    uint32_t int_no, err_code;
    // pushed by CPU automatically
    uint32_t eip, cs, eflags, useresp, ss;
} registers_t;


/***********************************************************/
// Consts

char *exception_messages[] = {
    "Division by zero",
    "Debug",
    "Reserved"
};

/***********************************************************/
// Globals

// Interrupt descriptor table
idt_gate_t idt[256];

/***********************************************************/
// Macros

// Macros for isolating the L&R half of the offset for the IDT gate
#define low_16(address) (uint16_t)((address) & 0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

/***********************************************************/

// Sets 
void set_idt_gate(int n, uint32_t handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].selector = 0x08; // see GDT
    idt[n].always0 = 0;
    // 0x8E = 1  00 0 1  110
    //        P DPL 0 D Type
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}

// void isr_handler(registers_t *r) {
//     print_string(exception_messages[r->int_no]);
//     print_nl();
// }

// void isr_install() {
//     set_idt_gate(0, (uint32_t) isr0);
//     set_idt_gate(1, (uint32_t) isr1);
//     // ...
//     set_idt_gate(31, (uint32_t) isr31);
// }
