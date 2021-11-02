include ../Makefile.comm

taget : libutil.a
	
libutil.a : util.o
	@(cd ../lib && ar cr libutil.a ../util/util.o)
util.o : util.cpp
	@(g++ $(CPPFLAGS) $(CXXFLAGS) -c util.cpp)

clean:
	@rm -f *.o ../lib/*.a
