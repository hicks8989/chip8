# include <vector>

# include "byte.h"
# include "display.h"
# include "memory.h"
# include "register.h"
# include "stack.h"
# include "timer.h"

// Registers
static Reg *V0 = new Reg();
static Reg *V1 = new Reg();
static Reg *V2 = new Reg();
static Reg *V3 = new Reg();
static Reg *V4 = new Reg();
static Reg *V5 = new Reg();
static Reg *V6 = new Reg();
static Reg *V7 = new Reg();
static Reg *V8 = new Reg();
static Reg *V9 = new Reg();
static Reg *VA = new Reg();
static Reg *VB = new Reg();
static Reg *VC = new Reg();
static Reg *VD = new Reg();
static Reg *VE = new Reg();

// Special Flag Register
static FlagReg *VF = new FlagReg();

static std::vector<Reg *> registers = {
    V0, V1, V2, V3, 
    V4, V5, V6, V7, 
    V8, V9, VA, VB, 
    VC, VD, VE, VF
};

// Program Counter and Index Register
static AddressReg *PC = new AddressReg();
static AddressReg *I = new AddressReg();

// Function Stack
static Stack *functionStack;

// RAM
static RAM *ram;

// Delay Timer
static DelayTimer *delayTimer;

// Sound Timer
static SoundTimer *soundTimer;

int main(int argc, char *argv[]) {
    return 0;
}