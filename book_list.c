#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "book_list.h"


int push(node_t ** head, const char * title, const char * author) { 
	book_t * data = NULL;
	node_t * new_node = NULL;

	data = malloc(sizeof(book_t));
	if (NULL == data) {
		return NO_MEMORY;
	}

	snprintf(data->title, strlen(title) + 1, "%s", title);
	snprintf(data->author, strlen(author) + 1, "%s", author);

	new_node = malloc(sizeof(node_t));
	if (NULL == new_node) {
		return NO_MEMORY;
	}
	new_node->data = data;

	if (NULL == *head) {
		new_node->next = NULL;
	}
	else {
		new_node->next = *head;
	}
	*head = new_node;
	return 0;
}


int pop(node_t ** head, book_t * return_data){
	node_t * node = NULL;
	
	if (NULL == *head) {
		return BOOK_LIST_EMPTY;
	}
	
	node = *head;
	copy_book(node->data, return_data);
	*head = (*head)->next;

	free(node->data);
	free(node);

	return 0;
}


int delete(node_t ** head, const char * title){ return NOT_IMPLEMENTED; }

int find_title(node_t * head, const char * title, book_t * return_data) {
	node_t * node = NULL;
	size_t length = 0;

	if (NULL == head) {
		return BOOK_LIST_EMPTY;
	}

	length = strlen(title) + 1;
	node = head;
	while (NULL != node) {
		if (strncmp(title, node->data->title, length) == 0) {
			copy_book(node->data, return_data);
			return 0;
		}
		node = node->next;
	}
	return BOOK_NOT_FOUND;
}


int sort(node_t * head, unsigned int flags){ return NOT_IMPLEMENTED; }

void print_list(node_t * head) {
	node_t * node = head;
	if (NULL == node) {
		puts("Empty list");
	}

	while (NULL != node) {
		printf("%s %s\n", node->data->title, node->data->author);
		node = node->next;
	}
}


int book_cmp(const book_t * book1, const book_t * book2) {
	int ret_val = strncmp(book1->title, book2->title, MAX_STRING);
	if (0 != ret_val) {
		return ret_val;
	}
	return strncmp(book1->author, book2->author, MAX_STRING);
}

int copy_book(const book_t * src, book_t * dest) {
	size_t title_len = 0, author_len = 0;

	title_len = strlen(src->title) + 1; // Account for null
	author_len = strlen(src->author) + 1; // Account for null

	memcpy(dest->title, src->title, title_len);
	memcpy(dest->author, src->author, author_len);

	return 0;
}

