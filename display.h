# ifndef DISPLAY_H
# define DISPLAY_H

# include <SFML/Graphics.hpp>
# include <vector>

# include "byte.h"
# include "register.h"

class Display {
    private:
    int width, height;
    std::vector<std::vector<Bit>> screen;
    sf::RenderWindow *window;
    sf::Texture texture;
    sf::Sprite sprite;

    public:
    Display(bool superchip);
    void clear();
    Bit draw(Reg *VX, Reg *VY, std::vector<Byte> sprite, Nibble N);
    void refresh();
};

#endif