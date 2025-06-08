# ifndef TIMER_H
# define TIMER_H

# include "byte.h"

class Timer {
    private:
    Byte timer;

    public:
    Timer();
    void dec();
    void set(Byte value);
    Byte get() const;
};

class DelayTimer : public Timer {

};

class SoundTimer : public Timer {

};

#endif
