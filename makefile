CXX         = c++ -std=c++17
CXXFLAGS    = -g -Wall
OBJS        = chip8.o display.o memory.o peripherals.o register.o timer.o
PROG        = chip8

all:        $(PROG)

$(PROG):    $(OBJS)
	$(CXX) -o $(PROG) $(OBJS)

clean:
	$(RM) $(PROG) core *.o
