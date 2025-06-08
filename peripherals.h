# ifndef PERIPHERALS_H
# define PERIPHERALS_H

# include "byte.h"

class Keyboard {
    private:
    static const char grid[4][4];

    public:
    bool getKey(Byte &key) const;
};

#endif
