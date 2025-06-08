# include <cassert>

# include "display.h"

Display::Display() {
    clear();
}

void Display::clear() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            screen[i][j] = 0;
        }
    }

    refresh();
}

Bit Display::draw(Reg *VX, Reg *VY, std::vector<Byte> sprite, Nibble N) {
    Bit flag = 0;
    Byte x = VX->read() % WIDTH;
    Byte y = VY->read() % HEIGHT;

    for (int i = 0; i < N; i++) {
        Byte py = y + i;
        Byte row = sprite[i]; 

        if (py >= HEIGHT) break;
        for (int j = 0; j < 8; j++) {
            Byte px = x + j;

            if (px >= WIDTH) break;
            if ((row & (0x80 >> j)) == 0) continue;

            Byte px = (x + j) % WIDTH;
            Byte py = (y + i) % HEIGHT;

            if (screen[px][py]) {
                flag = 1;
            }

            screen[px][py] ^= 1;
        }
    }

    refresh();
    return flag;
}

void Display::refresh() {

}
