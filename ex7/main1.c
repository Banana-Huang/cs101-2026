#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum { MAX_TICKETS = 5, NUMBER_COUNT = 7, MAX_NUMBER = 69 };

static int compare_numbers(const void *left, const void *right)
{
    return *(const int *)left - *(const int *)right;
}

static void draw_numbers(int numbers[NUMBER_COUNT])
{
    int drawn[MAX_NUMBER + 1] = {0};
    int accepted = 0;

    /* Discard the extra values so all 69 numbers have the same probability. */
    const unsigned int range = (unsigned int)RAND_MAX + 1u;
    const unsigned int limit = range - range % MAX_NUMBER;

    while (accepted < NUMBER_COUNT) {
        unsigned int value = (unsigned int)rand();
        if (value >= limit) {
            continue;
        }

        int number = (int)(value % MAX_NUMBER) + 1;
        if (!drawn[number]) {
            numbers[accepted++] = number;
            drawn[number] = 1;
        }
    }

    /* The sample sorts the first six numbers and displays the last separately. */
    qsort(numbers, NUMBER_COUNT - 1, sizeof numbers[0], compare_numbers);
}

int main(void)
{
    char input[80];
    char *end;

    puts("歡迎光臨長庚樂透彩購買機台");
    printf("請問您要買幾組樂透彩（1～5）：");
    fflush(stdout);
    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("讀取組數失敗。\n", stderr);
        return EXIT_FAILURE;
    }

    long count = strtol(input, &end, 10);
    while (isspace((unsigned char)*end)) {
        ++end;
    }
    if (count < 1 || count > MAX_TICKETS || *end != '\0' ||
        (strchr(input, '\n') == NULL && !feof(stdin))) {
        fputs("請輸入 1 到 5 之間的整數。\n", stderr);
        return EXIT_FAILURE;
    }

    time_t now = time(NULL);
    const char *timestamp = now == (time_t)-1 ? NULL : ctime(&now);
    if (timestamp == NULL) {
        fputs("無法取得目前時間。\n", stderr);
        return EXIT_FAILURE;
    }
    srand((unsigned int)now);

    FILE *ticket = fopen("lotto.txt", "w");
    if (ticket == NULL) {
        perror("lotto.txt");
        return EXIT_FAILURE;
    }

    fputs("======== lotto649 =========\n", ticket);
    fprintf(ticket, "= %.24s =\n", timestamp);

    for (int row = 1; row <= MAX_TICKETS; ++row) {
        fprintf(ticket, "[%d]:", row);
        if (row <= count) {
            int numbers[NUMBER_COUNT];
            draw_numbers(numbers);
            for (int i = 0; i < NUMBER_COUNT; ++i) {
                fprintf(ticket, " %02d", numbers[i]);
            }
        } else {
            fputs(" -- -- -- -- -- -- --", ticket);
        }
        fputc('\n', ticket);
    }

    fputs("======== csie@CGU =========\n", ticket);
    int write_failed = ferror(ticket);
    if (fclose(ticket) == EOF || write_failed) {
        fputs("寫入 lotto.txt 失敗。\n", stderr);
        return EXIT_FAILURE;
    }

    printf("已將您購買的 %ld 組樂透組合輸出至 lotto.txt。\n", count);
    return EXIT_SUCCESS;
}
