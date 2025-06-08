# include <cassert>

# include "display.h"

Display::Display(bool superchip) {
    if (superchip) {
        width = 128;
        height = 64;
    }
    else {
        width = 64;
        height = 32;
    }

    screen = std::vector<std::vector<Bit>>(width, std::vector<Bit>(height, 0));
    window = new sf::RenderWindow(sf::VideoMode(width * 10, height * 10), "CHIP-8");

    texture.create(width, height);
    sprite.setTexture(texture);
    sprite.setScale({10, 10});

    refresh();
}

void Display::clear() {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            screen[i][j] = 0;
        }
    }

    refresh();
}

Bit Display::draw(Reg* VX, Reg* VY, std::vector<Byte> spriteData, Nibble N) {
    Bit flag = 0;
    Byte x = VX->read() % width;
    Byte y = VY->read() % height;

    for (int i = 0; i < N; i++) {
        Byte py = y + i;
        if (py >= height) break;

        Byte row = spriteData[i];
        for (int j = 0; j < 8; j++) {
            Byte px = x + j;
            if (px >= width) break;
            if ((row & (0x80 >> j)) == 0) continue;

            if (screen[px][py]) flag = 1;
            screen[px][py] = screen[px][py] ^ 1;
        }
    }

    refresh();
    return flag;
}

void Display::refresh() {
    std::vector<sf::Uint8> pixels(width * height * 4, 0);

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int index = (j * width + i) * 4;
            sf::Uint8 color = screen[i][j] ? 255 : 0;
            pixels[index + 0] = color;
            pixels[index + 1] = color;
            pixels[index + 2] = color;
            pixels[index + 3] = 255;
        }
    }

    texture.update(pixels.data());

    window->clear();
    window->draw(sprite);
    window->display();
}
