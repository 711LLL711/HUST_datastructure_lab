#include "head.h"

void inputans(int a[9][9]) {
    char s[10];
    char c;
    printf("Please input the answer:\n");
    printf("Format: row col num\n");
    printf("Example: 123\n");
    printf("input q to end your input\n");
    while (scanf("%s", s) != EOF && s[0] != 'q') {
        int row = s[0] - '0';
        int col = s[1] - '0';
        int num = s[2] - '0';
        a[row-1][col-1] = num;
        printf("row:%d col:%d num:%d\n", row, col, num);
        //c = getchar();
        //printf("c = %c", c);
    }
   /* printf("a:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }*/
}

