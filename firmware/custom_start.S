#include "custom_ops.S"

    .section .text
    .global _start
    .global main

_start:
reset_vec:
    // PicoRV32 IRQ initialization (optional, masks all interrupts)
    picorv32_waitirq_insn(zero)
    picorv32_maskirq_insn(zero, zero)

    // 1. Zero all general-purpose registers (x1 - x31)
    li x1,  0; li x2,  0; li x3,  0; li x4,  0
    li x5,  0; li x6,  0; li x7,  0; li x8,  0
    li x9,  0; li x10, 0; li x11, 0; li x12, 0
    li x13, 0; li x14, 0; li x15, 0; li x16, 0
    li x17, 0; li x18, 0; li x19, 0; li x20, 0
    li x21, 0; li x22, 0; li x23, 0; li x24, 0
    li x25, 0; li x26, 0; li x27, 0; li x28, 0
    li x29, 0; li x30, 0; li x31, 0

    // 2. Set Stack Pointer to top of 128 KB RAM (0x20000)
    lui sp, (128 * 1024) >> 12

    // 3. Jump to C main function
    jal ra, main

    // 4. Signal success to testbench (write 123456789 to 0x20000000)
    lui a0, 0x20000000 >> 12
    li  a1, 123456789
    sw  a1, 0(a0)

    // 5. Halt simulation via CPU trap
    ebreak

loop_hang:
    j loop_hang
