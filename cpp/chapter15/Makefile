ROOT=..
include $(ROOT)/Makefile.comm
main : main.o
	@(g++ main.o $(LDDIR) $(LDLIBS) -o main)
main.o : main.cpp
	@(g++ $(CPPFLAGS) $(CXXFLAGS) -c main.cpp)
clean:
	@rm -f main main.o
