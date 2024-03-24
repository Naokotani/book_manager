#include "book.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

Book* books;
size_t bookSize;

int loadBooks() {
  books = read_data("books.dat", &bookSize);
  if (books == NULL) {
    fprintf(stderr, "Array not initailized");
    return 1;
  } else {
    return 0;
  }
}

void addBook() {
  bookSize += 1;
  books = realloc(books, sizeof(Book)* bookSize);

  Book book;
  char year[5];

  puts("Please enter a book title.");
  fgets(book.title, 256, stdin);
  book.title[strcspn(book.title, "\n")] = 0;

  puts("Please enter an author.");
  fgets(book.author, 100, stdin);
  book.author[strcspn(book.author, "\n")] = 0;

  puts("Please enter a 13 digit ISBN number.");
  fgets(book.isbn, 15, stdin);
  book.isbn[strcspn(book.isbn, "\n")] = 0;
  
  puts("Please enter a publishing year.");
  fgets(year, 5, stdin);
  book.year = strtol(year, (char **)NULL, 10);

  size_t i = bookSize - 1;
  books[i] = book;

  printf("\n--- Book Added ---\n");
  printf("%s\n", books[i].title);
  printf("%s\n", books[i].author);
  printf("%s\n", books[i].isbn);
  printf("%d\n", books[i].year);
}

void deleteBook() {
  char isbn[15];
  int found = false;

  puts("Please enter a 13 digit ISBN number to search");

  fgets(isbn, 15, stdin);
  isbn[strcspn(isbn, "\n")] = 0;
  int i;
  for (i = 0; i < bookSize; i++) {
    if (strcmp(books[i].isbn, isbn) == 0) {
      found = true;
      break;
    }
  }

  if (found == true) {
    for (i = i; i < bookSize - 1; i++) {
      books[i] = books[i + 1];
    }

    bookSize -= 1;
    books = realloc(books, sizeof(Book) * bookSize);
  } else {
    puts("Book not found.");
  }
}

void searchBook() {
  char isbn[15];

  puts("Please enter a 13 digit ISBN number to search");

  fgets(isbn, 15, stdin);
  isbn[strcspn(isbn, "\n")] = 0;

  for (int i = 0; i < bookSize; i++) {
    if (strcmp(books[i].isbn, isbn) == 0) {
      printf("\n--- %s ---\n", books[i].title);
      printf("%s\n", books[i].author);
      printf("%s\n", books[i].isbn);
      printf("%d\n", books[i].year);
      printf("\n------\n");
    }
  }
}

void listBooks() {
  for (int i = 0; i < bookSize; i++) {
    printf("\n--- %s ---\n", books[i].title);
    printf("%s\n", books[i].author);
    printf("%s\n", books[i].isbn);
    printf("%d\n", books[i].year);
    printf("\n------\n");
  }
}

int saveBooks() {
  if (write_data("books.dat", books, bookSize)) {
    printf("Books loaded\n");
    return 0;
  } else {
    printf("Error saving books");
    return 1;
  }
  free(books);
}

bool write_data(char *filename, Book *data, size_t total) {
  FILE *file;
  file = fopen(filename, "wb");

  if (file == NULL) return false;

  if (fwrite(&total, sizeof(size_t), 1, file) != 1)
    return false;

  if (fwrite(data, sizeof(Book), total, file) != total)
    return false;

  if (fclose(file) == EOF)
    return false;

  return true;
}

Book *read_data(char *filename, size_t *total) {
  FILE *file;
  file = fopen(filename, "rb");

  if (file == NULL) return NULL;

  if (fread(total, sizeof(size_t), 1, file) != 1)
    return NULL;

  Book *data = malloc(sizeof(Book) * *total);

  if (fread(data, sizeof(Book), *total, file) != *total) {
    free(data);
    return NULL;
  }

  if (fclose(file) == EOF) {
    free(data);
    return false;
  }

  return data;

}
