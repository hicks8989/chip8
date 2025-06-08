# include <cassert>

# include "memory.h"

Instruction RAM::fetch(AddressReg *pc) const {
    Byte lo, hi;
    Address addr = pc->read();
    assert(addr + 2 <= 4096);

    // Read in the low and high bytes
    lo = memory[addr++];
    hi = memory[addr++];

    // Increment the program counter by 2 and return the instruction
    pc->write(addr);
    return lo | ((Instruction)hi << 8);
}
