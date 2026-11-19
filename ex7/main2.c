#include <stdio.h>
#include <stdlib.h>

typedef struct Books {
    int id;
    int price;
    char title[64];
} book_t;

static int total_price(const book_t books[], size_t count)
{
    int total = 0;

    for (size_t i = 0; i < count; ++i) {
        total += books[i].price;
    }
    return total;
}

static void list_books(const book_t books[], size_t count)
{
    printf("%-4s %6s  %s\n", "ID", "Price", "Title");
    for (size_t i = 0; i < count; ++i) {
        printf("%-4d %6d  %s\n", books[i].id, books[i].price, books[i].title);
    }
}

int main(void)
{
    const book_t books[] = {
        {1, 1000, "All the Light We Cannot See"},
        {2, 300, "The 38 Letters from J.D. Rockefeller to his son"},
        {3, 1000, "The Ballad of Songbirds and Snakes"},
        {4, 550, "Killers of the Flower Moon"},
        {5, 870, "Elon Musk"},
        {6, 1344, "Milk and Honey 12-Month 2024"}
    };
    const size_t count = sizeof books / sizeof books[0];

    FILE *file = fopen("Book.bin", "wb");
    if (file == NULL) {
        perror("Book.bin");
        return EXIT_FAILURE;
    }

    size_t written = fwrite(books, sizeof books[0], count, file);
    if (fclose(file) == EOF || written != count) {
        fputs("Could not write Book.bin.\n", stderr);
        return EXIT_FAILURE;
    }

    list_books(books, count);
    printf("Total price: %d\n", total_price(books, count));
    return EXIT_SUCCESS;
}
