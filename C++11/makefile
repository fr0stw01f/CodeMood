OBJS = main.o ScopeGuard.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
main: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
main.o: main.cpp
	g++ ${CPPFLAGS} -c main.cpp -o $@
ScopeGuard.o: ScopeGuard.cpp
	g++ ${CPPFLAGS} -c ScopeGuard.cpp -o $@
clean:
	rm -f main ${OBJS}
