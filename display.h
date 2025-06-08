# ifndef DISPLAY_H
# define DISPLAY_H

# include "byte.h"
# include "register.h"

const int WIDTH = 64, HEIGHT = 32;

class Display {
    private:
    Bit screen[WIDTH][HEIGHT];

    public:
    Display();
    void clear();
    void draw(Reg *VX, Reg *VY, Nibble N);
    void refresh();
};

#endif