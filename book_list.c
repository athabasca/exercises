#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "book_list.h"


int push(node_t * head, const char * title, const char * author) { 
	book_t * data = NULL;
	node_t * new_node = NULL;

	data = malloc(sizeof(book_t));
	if (NULL == data) {
		return NO_MEMORY;
	}

	snprintf(data->title, strlen(title), "%s", title);
	snprintf(data->author, strlen(author), "%s", author);

	new_node = malloc(sizeof(node_t));
	if (NULL == new_node) {
		return NO_MEMORY;
	}
	new_node->data = data;

	if (NULL == head) {
		new_node->next = NULL;
		head = new_node;
	}
	else {
		new_node->next = head->next;
		head->next = new_node;
	}
	return 0;
}


int pop(node_t ** head, book_t * return_data){ return -1; }
int delete(node_t ** head, const char * title){ return -1; }

int find_title(node_t * head, const char * title, book_t * return_data) {
	node_t * node = NULL;
	size_t length = 0;

	if (NULL == head) {
		return BOOK_LIST_EMPTY;
	}

	length = strlen(title);
	node = head;
	while (NULL != node) {
		if (strncmp(title, node->data->title, length) == 0) {
			snprintf(return_data->title, length, "%s", node->data->title);
			snprintf(return_data->author, strlen(node->data->author), "%s", node->data->author);
			return 0;
		}
		node = node->next;
	}
	return BOOK_NOT_FOUND;
}


int find_index(node_t * head, const unsigned int index, book_t * return_data) { return -1; }
int sort(node_t * head, unsigned int flags){ return -1; }

void print_list(node_t * head) {
	node_t * node = head;
	if (NULL == node) {
		return;
	}

	while (NULL != node) {
		printf("%s %s\n", node->data->title, node->data->author);
		node = node->next;
	}
}
