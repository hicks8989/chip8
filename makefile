CXX         = c++ -std=c++17
CXXFLAGS    = -g -Wall
OBJS        = display.o memory.o register.o timer.o
PROG        = chip8

all:        $(PROG)

$(PROG):    $(OBJS)
	$(CXX) -o $(PROG) $(OBJS)

clean:
	$(RM) $(PROG) core *.o
