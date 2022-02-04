#ifndef BOOK_LIST_H
#define BOOK_LIST_H

/* Book list module
 *
 * Use this module to store the pile of books on your bedside table.
 * You may add or remove a book from the top of the pile, sort the pile,
 * search it for a particular book, or remove a particular book from
 * anywhere in the pile.
 */

typedef struct book {
	char * title;
	char * author;
} book_t;

typedef struct node {
	book_t * data;
	struct node * next;
} node_t;

/* Return codes */
#define BOOK_LIST_EMPTY -1
#define BOOK_NOT_FOUND -2
#define NO_MEMORY -3

/* Sorting flags */
#define BOOK_SORT_TITLE 0x1
#define BOOK_SORT_AUTHOR 0x2
#define BOOK_SORT_REVERSE 0x4

/* Push a book on top of the pile
 *
 * The push() function creates a new node using the title and author
 * parameters and inserts it at the front of the list pointed to by head.
 *
 * The push() function returns 0 on success 
 * or NO_MEMORY if it cannot allocate memory for the node.
 */
int push(node_t * head, const char * title, const char * author);


/* Pop a book off the top of the pile
 *
 * The pop() function removes the node at the front of the list pointed
 * to by head and stores the title and author in the return_data struct.
 *
 * The pop() function returns 0 on success
 * or BOOK_LIST_EMPTY if the list is empty.
 */
int pop(node_t ** head, book_t * return_data);


/* Remove a book with a given title
 *
 * The delete() function removes the book with the provided title from
 * the list pointed to by head. If more than one book has that title,
 * it removes the first one.
 *
 * The delete() function returns 0 on success,
 * BOOK_NOT_FOUND if the book is not in the list,
 * or BOOK_LIST_EMPTY if the list is empty.
 */
int delete(node_t ** head, const char * title);


/* Find a book with a given title
 *
 * The find() function returns the title and author of a book with a
 * given title if the book is in the list pointed to by head.
 * The title and author are stored in the return_data struct.
 *
 * The find() function returns 0 on success,
 * BOOK_NOT_FOUND if the book is not in the list,
 * or BOOK_LIST_EMPTY if the list is empty.
 */
int find(node_t * head, const char * title, book_t * return_data);


/* Sort the pile of books
 *
 * The sort() function sorts the list pointed to by head in case-insensitive
 * alphabetic order. The flags parameter specifies whether to sort by title
 * or author, and optionally to reverse the sorting order.
 * If BOOK_SORT_TITLE and BOOK_SORT_AUTHOR are both provided, or neither,
 * sort() uses the title. BOOK_SORT_REVERSE reverses the sort.
 *
 * The sort() function returns 0 on success
 * or BOOK_LIST_EMPTY if the list is empty.
 */
int sort(node_t * head, unsigned int flags);


#endif

