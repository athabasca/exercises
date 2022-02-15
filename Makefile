SRCS = book_list.c book_list.h
TEST_SRCS = tests.c $(SRCS)

CFLAGS = -Wall

all: $(TEST_SRCS) 
	gcc $(CFLAGS) $^ -o test

.PHONY: test
test:
	./test

.PHONY: clean
clean:
	rm -f test *.gch
