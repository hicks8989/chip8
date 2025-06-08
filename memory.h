# ifndef MEMORY_H
# define MEMORY_H

# include "byte.h"
# include "register.h"

class RAM {
    private:
    Byte memory[4096];

    public:
    RAM();
    Instruction fetch(AddressReg *pc) const;
};

#endif