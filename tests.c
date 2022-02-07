#include <stdio.h>
#include <string.h>
#include "book_list.h"

const book_t books[] = 
	{ "Starfish", "Peter Watts" },
	{ "Neuromancer", "William Gibson" },
	{ "Isekai", "Protia Du Alleb" },
	{ "I Shall Wear Midnight", "Terry Pratchett" }
};

const book_t missing_book = { "Velvet Darkness", "Sofia Garcia Moreno" };

int test_push(void) {
	node_t * head = NULL;
	book_t found_book;

	if (push(head, books[1].title, books[1].author) == 0) {
		if (find(head, books[1].title, &found_book) == 0) {
			if (strcmp(books[1].title, found_book.title) == 0
				&& strcmp(books[1].author, found_book.author) == 0)
			{
				return 0;
			}
		}
	}
	return -1;
}

int test_push_three(void) {
	return -1;
}

int test_push_nomem(void) {
	/* How do you test malloc failure? */
	return -1;
}

int test_pop(void) {
	return -1;
}

int test_pop_two_of_three(void) {
	return -1;
}

int test_pop_empty(void) {
	return -1;
}

int test_delete_first(void) {
	return -1;
}

int test_delete_middle(void) {
	return -1;
}

int test_delete_last(void) {
	return -1;
}

int test_delete_empty(void) {
	return -1;
}

int test_delete_missing_book(void) {
	return -1;
}

int test_find(void) {
	return -1;
}

int test_find_empty(void) {
	return -1;
}

int test_find_missing_book(void) {
	return -1;
}

int test_sort(void) {
	return -1;
}

int test_sort_one(void) {
	return -1;
}

int test_sort_empty(void) {
	return -1;
}

struct test_fn {
	int (*fn_ptr)(void);
	char * name;
};

/* Struct populated with :r!grep -o "test_[a-zA-Z_]*" tests.c | awk '{print "{ &"$0", \""$0"\" },"}' */
struct test_fn tests[] = {
	{ &test_push, "test_push" },
	{ &test_push_three, "test_push_three" },
	{ &test_push_nomem, "test_push_nomem" },
	{ &test_pop, "test_pop" },
	{ &test_pop_two_of_three, "test_pop_two_of_three" },
	{ &test_pop_empty, "test_pop_empty" },
	{ &test_delete_first, "test_delete_first" },
	{ &test_delete_middle, "test_delete_middle" },
	{ &test_delete_last, "test_delete_last" },
	{ &test_delete_empty, "test_delete_empty" },
	{ &test_delete_missing_book, "test_delete_missing_book" },
	{ &test_find, "test_find" },
	{ &test_find_empty, "test_find_empty" },
	{ &test_find_missing_book, "test_find_missing_book" },
	{ &test_sort, "test_sort" },
	{ &test_sort_one, "test_sort_one" },
	{ &test_sort_empty, "test_sort_empty" }
};

int main(void) {
	unsigned int num_tests = sizeof(tests)/sizeof(tests[0]);
	unsigned int ii = 0;
	int ret_val = 0;

	for ( ; ii < num_tests; ii++) {
		ret_val = (*tests[ii].fn_ptr)();

		if (0 == ret_val) {
			printf("passed %s\n", tests[ii].name);
		}
		else {
			printf("failed %s\n", tests[ii].name);
		}
	}
	return 0;
}
