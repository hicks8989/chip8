# include "timer.h"

void Timer::set(Byte value) {
    timer = value;
}

Byte Timer::get() const {
    return timer;
}