SRCS = book_list.c book_list.h
TEST_SRCS = tests.c $(SRCS)

CFLAGS = -Wall

test: $(TEST_SRCS) 
	gcc $(CFLAGS) $^ -o $@
	./$@

.PHONY: clean
clean:
	rm -f test *.gch
