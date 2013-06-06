OBJS = ExceptionSafe.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
ExceptionSafe: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
ExceptionSafe.o: ExceptionSafe.cpp
	g++ ${CPPFLAGS} -c ExceptionSafe.cpp -o $@
clean:
	rm -f ExceptionSafe ${OBJS}
