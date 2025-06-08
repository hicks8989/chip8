# ifndef DISPLAY_H
# define DISPLAY_H

# include <vector>

# include "byte.h"
# include "register.h"

const int WIDTH = 64, HEIGHT = 32;

class Display {
    private:
    Bit screen[WIDTH][HEIGHT];

    public:
    Display();
    void clear();
    Bit draw(Reg *VX, Reg *VY, std::vector<Byte> sprite, Nibble N);
    void refresh();
};

#endif