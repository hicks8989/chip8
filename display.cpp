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
}

void Display::draw(Reg *X, Reg *Y, Nibble N) {

}

void Display::refresh() {

}
