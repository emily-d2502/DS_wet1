CC = clang++
OBJS = build/maina1.o build/StreamingDBa1.o build/User.o build/Movie.o build/Group.o
PROG_NAME = main
COMP_FLAG = -std=c++11 
AVL_FILES = AVL/AVL.h AVL/Node.h AVL/avl_utilities.h AVL/class_defines.h

$(PROG_NAME) : $(OBJS)
	$(CC) -o $(PROG_NAME) $(OBJS) 

build/maina1.o: maina1.cpp
	$(CC) -c $(COMP_FLAG) maina1.cpp
	mv maina1.o build

build/StreamingDBa1.o: StreamingDBa1.cpp
	$(CC) -c $(COMP_FLAG) StreamingDBa1.cpp
	mv StreamingDBa1.o build

build/User.o: Classes/User.cpp
	$(CC) -c $(COMP_FLAG) Classes/User.cpp
	mv User.o build

build/Movie.o: Classes/Movie.cpp
	$(CC) -c $(COMP_FLAG) Classes/Movie.cpp
	mv Movie.o build

build/Group.o: Classes/Group.cpp
	$(CC) -c $(COMP_FLAG) Classes/Group.cpp
	mv Group.o build

.PHONY: clean
clean:
	rm -f $(PROG_NAME) $(OBJS)

