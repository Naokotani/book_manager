#include <stdio.h>
#include "book.h"

int main() {
    int choice;
    loadBooks();

    while (1) {
        printf("\n--- Book Management System ---\n");
        printf("1. Add Book\n2. Delete Book\n3. Search Books\n4. List All Books\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1: addBook(); break;
            case 2: deleteBook(); break;
            case 3: searchBook(); break;
            case 4: listBooks(); break;
            case 5: return saveBooks(); 
            default: printf("Invalid choice. Please try again.\n");
        }
    }
}
