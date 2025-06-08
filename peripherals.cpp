# include <windows.h>

# include "peripherals.h"

const char Keyboard::grid[4][4] = {
    { '1', '2', '3', '4' },
    { 'Q', 'W', 'E', 'R' },
    { 'A', 'S', 'D', 'F' },
    { 'Z', 'X', 'C', 'V' }
};

bool Keyboard::getKey(Byte &key) const {
    Byte vk;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            vk = VkKeyScanA(grid[i][j]) & 0xFF;
            if (GetAsyncKeyState(vk) & 0x8000) {
                key = i * 4 + j;
                return true;
            }
        }
    }

    return false;
}