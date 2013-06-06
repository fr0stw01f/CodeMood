OBJS = main.o utils.o
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
main: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
main.o: main.cpp
	g++ ${CPPFLAGS} -c main.cpp -o $@
utils.o: utils.cpp
	g++ ${CPPFLAGS} -c utils.cpp -o $@
clean:
	rm -f main ${OBJS}
