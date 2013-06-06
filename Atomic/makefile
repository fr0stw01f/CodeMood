OBJS = atomic.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
atomic: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS} ${LIBS}
atomic.o: atomic.cpp
	g++ ${CPPFLAGS} -c atomic.cpp -o $@
clean:
	rm -f atomic ${OBJS}
