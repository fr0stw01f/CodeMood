OBJS = Sorting.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11 -O2
LDFLAGS = -lpthread
Sorting: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS} ${LIBS}
Sorting.o: Sorting.cpp
	g++ ${CPPFLAGS} -c Sorting.cpp -o $@
clean:
	rm -f Sorting ${OBJS}
