CC = clang++
TEST_OBJS = testing.o
TEST_NAME = test
DEBUG_FLAG = -std=c++11 -g -DNDEBUG -Wall

$(TEST_NAME) : $(TEST_OBJS)
	$(CC) -o $(TEST_NAME) $(TEST_OBJS)

testing.o: testing.cpp
	$(CC) -c $(DEBUG_FLAG) testing.cpp

.PHONY: clean
clean:
	rm -f $(TEST_NAME) $(TEST_OBJS)

