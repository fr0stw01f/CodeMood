OBJS = GotW.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
GotW: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
GotW.o: GotW.cpp
	g++ ${CPPFLAGS} -c GotW.cpp -o $@
clean:
	rm -f GotW ${OBJS}
