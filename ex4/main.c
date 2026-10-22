
#include <stdio.h>

int main(void) {
    FILE *fp;

    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1f, 1.2f, 1.3f};

    int ra[3];
    char rb[4];
    float rc[3];

    // 開啟檔案並寫入二進位資料
    fp = fopen("a.bin", "wb");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }

    fwrite(a, sizeof(int), 3, fp);
    fwrite(b, sizeof(char), 4, fp);
    fwrite(c, sizeof(float), 3, fp);

    fclose(fp);

    // 重新開啟檔案並讀取資料
    fp = fopen("a.bin", "rb");
    if (fp == NULL) {
        printf("Cannot open file!\n");
        return 1;
    }

    fread(ra, sizeof(int), 3, fp);
    fread(rb, sizeof(char), 4, fp);
    fread(rc, sizeof(float), 3, fp);

    fclose(fp);

    // 輸出三個陣列
    for (int i = 0; i < 3; i++)
        printf("%d ", ra[i]);

    printf("\n%s\n", rb);

    for (int i = 0; i < 3; i++)
        printf("%f ", rc[i]);

    printf("\n");

    return 0;
}
