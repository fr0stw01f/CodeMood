OBJS = OpenMP.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11 -O2 -fopenmp `pkg-config --cflags opencv` 
LDFLAGS = -fopenmp `pkg-config --libs opencv`
OpenMP: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
OpenMP.o: OpenMP.cpp
	g++ ${CPPFLAGS} -c OpenMP.cpp -o $@
clean:
	rm -f OpenMP ${OBJS}
