OBJS = PrintBinaryTreeByLevel.o
LIBS = libgtest.a
CPPFLAGS = -Wall -std=c++11
LDFLAGS = -lpthread
PrintBinaryTreeByLevel: ${OBJS} 
	g++ ${LDFLAGS} -o $@ ${OBJS}
PrintBinaryTreeByLevel.o: PrintBinaryTreeByLevel.cpp
	g++ ${CPPFLAGS} -c PrintBinaryTreeByLevel.cpp -o $@
clean:
	rm -f PrintBinaryTreeByLevel ${OBJS}
