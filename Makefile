CC = clang++
OBJS = main.o 
TEST_OBJS = testing_avl.o
PROG_NAME = main
TEST_NAME = test
DEBUG_FLAG = -g
COMP_FLAG = -std=c++11
AVL_FILES = AVL/AVL.h AVL/Node.h AVL/avl_utilities.h AVL/class_defines.h


$(PROG_NAME) : $(OBJS)
	$(CC) -o $(PROG_NAME) $(OBJS)

$(TEST_NAME) : $(TEST_OBJS)
	$(CC) -o $(TEST_NAME) $(TEST_OBJS)

main.o: main.cpp macros.h
	$(CC) -c $(COMP_FLAG) main.cpp

testing_avl.o: testing_avl.cpp macros.h $(AVL_FILES)
	$(CC) -c $(COMP_FLAG) testing_avl.cpp

.PHONY: clean
clean:
	rm -f $(PROG_NAME) $(TEST_NAME) $(OBJS) $(TEST_OBJS)

