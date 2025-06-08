# include <cassert>
# include <random>
# include <vector>

# include "byte.h"
# include "display.h"
# include "memory.h"
# include "register.h"
# include "stack.h"
# include "timer.h"

// Random generator
static std::random_device rd;
static std::mt19937 gen(rd());

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

// Display
static Display *display;

// Delay Timer
static DelayTimer *delayTimer;

// Sound Timer
static SoundTimer *soundTimer;

// Instructions
void clearScreen() {
    display->clear();
}

void jump(Address NNN) {
    assert(NNN <= 0x0FFF);
    PC->write(NNN);
}

void callSubroutine(Address NNN) {
    assert(NNN <= 0x0FFF);
    functionStack->push(PC->read());
    jump(NNN);
}

void endSubroutine() {
    assert(!functionStack->empty());
    Address last = functionStack->top();

    functionStack->pop();
    jump(last);
}

void skipConditionally(Reg *VX, Byte NN, bool skipIfEqual) {
    Byte x = VX->read();

    if ((x == NN) == skipIfEqual) {
        PC->write(PC->read() + 2);
    }
}

void skipConditionally(Reg *VX, Reg *VY, bool skipIfEqual) {
    Byte x = VX->read();
    Byte y = VY->read();

    if ((x == y) == skipIfEqual) {
        PC->write(PC->read() + 2);
    }
}

void set(Reg *VX, Byte NN) {
    VX->write(NN);
}

void set(Reg *VX, Reg *VY) {
    Byte y = VY->read();
    VX->write(y);
}

void add(Reg *VX, Byte NN) {
    Byte x = VX->read();

    Address sum = static_cast<Address>(x) + static_cast<Address>(NN);
    VX->write(static_cast<Byte>(sum));
}

void add(Reg *VX, Reg *VY) {
    Byte x = VX->read();
    Byte y = VY->read();

    Address sum = static_cast<Address>(x) + static_cast<Address>(y);
    VX->write(static_cast<Byte>(sum));
    VF->write_flag(sum > 0xFF);
}

void binaryOr(Reg *VX, Reg *VY) {
    Byte x = VX->read();
    Byte y = VY->read();

    VX->write(x | y);
}

void binaryAnd(Reg *VX, Reg *VY) {
    Byte x = VX->read();
    Byte y = VY->read();

    VX->write(x & y);
}

void binaryXor(Reg *VX, Reg *VY) {
    Byte x = VX->read();
    Byte y = VY->read();

    VX->write(x ^ y);
}

void subtract(Reg *VX, Reg *VY, bool reverseOrder) {
    Byte difference;
    Byte x = VX->read();
    Byte y = VY->read();

    if (reverseOrder) {
        difference = y - x;
    } else {
        difference = x - y;
    }

    VX->write(difference);
    VF->write_flag(difference >= 0);
}

void shift(Reg *VX, Reg *VY) {

}

void setIndex(Address NNN) {
    assert(NNN <= 0x0FFF);
    I->write(NNN);
}

void jumpWithOffset(Address NNN, bool superchip) {
    Address address;
    Nibble X = (0xF00 & NNN) >> 8;
    Reg *VX = superchip ? registers[X] : registers[0];

    address = NNN + VX->read();
    assert(address < 4096);
    jump(address);
}

void random(Reg *VX, Byte NN) {
    std::uniform_int_distribution<> distrib(0, 0xFF);
    Byte randomByte = static_cast<Byte>(distrib(gen));

    VX->write(randomByte & NN);
}

void draw(Reg *VX, Reg *VY, Nibble N) {
    std::vector<Byte> sprites(N);
    Address addr = I->read();

    for (int i = 0; i < N; i++) {
        sprites[i] = ram->read(addr++);
    }

    Bit flag = display->draw(VX, VY, sprites, N);
    VF->write_flag(flag);
}

// Instruction Decode
void decode(Instruction instruction) {
    // 4-bit nibbles from instruction
    Nibble X = (instruction & (0x0F00)) >> 8;  // Lookup one of the 16 byte registers VX
    Nibble Y = (instruction & (0x00F0)) >> 4;  // Lookup one of the 16 byte registers VY
    Nibble N = (instruction & (0x000F));       // A 4-bit number

    // 8-bit byte from instruction
    Byte NN = (instruction & (0x00FF));        // An 8-bit immediate number

    // 12-bit address from instruction
    Address NNN = (instruction & (0x0FFF));    // A 12-bit immediate memory address

    // Registers
    Reg *VX = registers[X];
    Reg *VY = registers[Y];

    // Execute Instruction
    if (instruction == 0x00E0) {
        // 0x00E0: (Clear Screen)
        clearScreen();
    } else if ((instruction & 0xF000) == 0x1000) {
        // 0x1NNN: (Jump to address NNN)
        jump(NNN);
    } else if ((instruction & 0xF000) == 0x6000) {
        // 0x6XNN: (Set register VX to NN)
        set(VX, NN);
    } else if ((instruction & 0xF000) == 0x7000) {
        // 0x7XNN: (Add NN to register VX)
        add(VX, NN);
    } else if ((instruction & 0xF000) == 0xA000) {
        // 0xANNN: (Set register I to NNN)
        setIndex(NNN);
    } else if ((instruction & 0xF000) == 0xD000) {
        // 0xDXYN: (Display/Draw)
        draw(VX, VY, N);
    }
}

int main(int argc, char *argv[]) {


    while (true) {
        Instruction instruction = ram->fetch(PC);
        decode(instruction);
    }
}