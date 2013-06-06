OBJS = main.o say_hello.o
CPPFLAGS = -Wall -std=c++11
main: ${OBJS} 
	g++ -o $@ ${OBJS}
main.o: main.cpp
	g++ ${CPPFLAGS} -c main.cpp -o $@
say_hello.o: say_hello.cpp
	g++ ${CPPFLAGS} -c say_hello.cpp -o $@
clean:
	rm -f main ${OBJS}
