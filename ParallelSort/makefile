OBJS = ParallelSort.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11 -O2
LDFLAGS = -ltbb
ParallelSort: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
ParallelSort.o: ParallelSort.cpp
	g++ ${CPPFLAGS} -c ParallelSort.cpp -o $@
clean:
	rm -f ParallelSort ${OBJS}
