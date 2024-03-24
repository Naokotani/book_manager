#ifndef BOOK_H
#define BOOK_H
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    char title[256];
    char author[100];
    char isbn[15]; // ISBN-13 format
    int year;
} Book;

void addBook();
void deleteBook();
void searchBook();
void listBooks();
int saveBooks();
int loadBooks();
bool write_data(char *filename, Book *data, size_t total);
Book *read_data(char *filename, size_t *total);

#endif
