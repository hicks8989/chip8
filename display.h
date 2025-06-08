# ifndef DISPLAY_H
# define DISPLAY_H

# include "byte.h"

static const int WIDTH = 64, HEIGHT = 32;

class Display {
    private:
    Bit screen[WIDTH][HEIGHT];

    public:
    Display();
};

#endif