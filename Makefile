CC = clang++
OBJS = maina1.o
PROG_NAME = maina1
COMP_FLAG = -std=c++11
AVL_FILES = AVL/AVL.h AVL/Node.h AVL/avl_utilities.h AVL/class_defines.h


$(PROG_NAME) : $(OBJS)
	$(CC) -o $(PROG_NAME) $(OBJS)

maina1.o: maina1.cpp
	$(CC) -c $(COMP_FLAG) -DNDEBUG -Wall maina1.cpp

main: main.o
	$(CC) -o main main.o

main.o: main.cpp
	$(CC) -c $(COMP_FLAG) main.cpp

.PHONY: clean
clean:
	rm -f $(PROG_NAME) $(OBJS)
	rm -f main main.o

