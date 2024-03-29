#include "head.h"
//将蜂窝数独问题规约成CNF问题
#define CORRECT 0
#define WRONG -1

//typedef struct numNode { //为翻转提供准备
//    int x;
//    int y;
//} numNode;
// 
//截止到每行之前所有的格子数，如s(3) = 5+6 = 11
int s[10] = { 0,5,11,18,26,35,43,50,56,61 };

//每格起始数
int num[10][10] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,0,9,18,27,36,-1,-1,-1,-1,-1,45,54,63,72,81,90,-1,-1,-1,-1,99,108,117,126,135,144,153,-1,-1,-1,162,171,180,189,198,207,216,225,-1,-1,234,243,252,261,270,279,288,297,306,-1,315,324,333,342,351,360,369,378,-1,-1,387,396,405,414,423,432,441,-1,-1,-1,450,459,468,477,486,495,-1,-1,-1,-1,504,513,522,531,540,-1,-1,-1,-1 };
//转化成自然顺序的函数
int toSemanticEncoding(int i, int j, int n, int* L) {
    return (L[i - 1] + (j - 1)) * 9 + n;
}

//语义编码转自然顺序编码
int TransLiteral(int x)
{
    for (int i = 1; i <= 5; i++)
        if (x >= 101 + 10 * i && x <= 109 + 10 * i)
            return x - (100 + 10 * i) + 9 * (i - 1);

    for (int i = 1; i <= 6; i++)
        if (x >= 201 + 10 * i && x <= 209 + 10 * i)
            return x - (200 + 10 * i) + 9 * (i - 1) + 9 * 5;

    for (int i = 1; i <= 7; i++)
        if (x >= 301 + 10 * i && x <= 309 + 10 * i)
            return x - (300 + 10 * i) + 9 * (i - 1) + 9 * 11;

    for (int i = 1; i <= 8; i++)
        if (x >= 401 + 10 * i && x <= 409 + 10 * i)
            return x - (400 + 10 * i) + 9 * (i - 1) + 9 * 18;

    for (int i = 1; i <= 9; i++)
        if (x >= 501 + 10 * i && x <= 509 + 10 * i)
            return x - (500 + 10 * i) + 9 * (i - 1) + 9 * 26;

    for (int i = 1; i <= 8; i++)
        if (x >= 601 + 10 * i && x <= 609 + 10 * i)
            return x - (600 + 10 * i) + 9 * (i - 1) + 9 * 35;

    for (int i = 1; i <= 7; i++)
        if (x >= 701 + 10 * i && x <= 709 + 10 * i)
            return x - (700 + 10 * i) + 9 * (i - 1) + 9 * 43;

    for (int i = 1; i <= 6; i++)
        if (x >= 801 + 10 * i && x <= 809 + 10 * i)
            return x - (800 + 10 * i) + 9 * (i - 1) + 9 * 50;

    for (int i = 1; i <= 5; i++)
        if (x >= 901 + 10 * i && x <= 909 + 10 * i)
            return x - (900 + 10 * i) + 9 * (i - 1) + 9 * 56;

    return 0;
}

void toDirectEncoding(int n,int* row,int* col,int* number) {
    int i,j;
    for (i = 1; i <= 9; i++) {
        for (j = 1; j <= 9 - abs(5 - i); j++) {
            if (n - num[i][j] < 10) {
                *row = i;
                *col = j;
                *number = n - num[i][j];
                //printf("row:%d col:%d num%d\n", *row, *col, *number);
                return;
            }
        }
    }

}

void createHanidoku(int a[],char* filename) {
    FILE* fis = fopen(filename, "r");
    if (!fis) printf("can't open this file!\n");

    char str[100];
    fscanf(fis, "%s", str);

    for (int i = 0; i < 61; i++)
        a[i] = str[5 + i] - '0';

    fclose(fis);
}

void createStartinggrid(int a[], int b[], int holes) {
    //从初始格局中随机挖空
    srand((unsigned)time(NULL));
    for (int i = 0; i < 61; i++) b[i] = a[i];

    int cf;
    int* c = (int*)malloc(sizeof(int) * holes);

    int flag = 0;

    for (int i = 0; i < holes; i++) {
        cf = rand() % 61;

        flag = 0;
        for (int m = 0; m < i; m++)
            if (cf == c[m])
                flag = 1;

        if (flag == 0) {
            b[cf] = 0;
            c[i] = cf;
        }
        else {
            i--;
        }
    }
    free(c);
}

void print(const int a[]) {
    //输出蜂窝数独
    printf("         / \\ / \\ / \\ / \\ / \\\n");
    printf("        |");
    for (int i = 0; i < 5; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("       / \\ / \\ / \\ / \\ / \\ / \\\n");
    printf("      |");
    for (int i = 5; i < 11; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("     / \\ / \\ / \\ / \\ / \\ / \\ / \\\n");
    printf("    |");
    for (int i = 11; i < 18; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("   / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\\n");
    printf("  |");
    for (int i = 18; i < 26; i++) printf(" %d |", a[i]);
    printf("\n");
    printf(" / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\\n");
    printf("|");
    for (int i = 26; i < 35; i++) printf(" %d |", a[i]);
    printf("\n");
    printf(" \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ /\n");
    printf("  |");
    for (int i = 35; i < 43; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("   \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ /\n");
    printf("    |");
    for (int i = 43; i < 50; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("     \\ / \\ / \\ / \\ / \\ / \\ / \\ /\n");
    printf("      |");
    for (int i = 50; i < 56; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("       \\ / \\ / \\ / \\ / \\ / \\ /\n");
    printf("        |");
    for (int i = 56; i < 61; i++) printf(" %d |", a[i]);
    printf("\n");
    printf("         \\ / \\ / \\ / \\ / \\ /\n");
}


//b是待输出的数组，把a数组逆时针旋转了60度
//a是待输出的数组，把b数组顺时针旋转了60度
void turnAnAngle(numNode a[][10], numNode b[][10])
{
    b[1][1] = a[1][5], b[1][2] = a[2][6], b[1][3] = a[3][7], b[1][4] = a[4][8], b[1][5] = a[5][9];
    b[2][1] = a[1][4], b[2][2] = a[2][5], b[2][3] = a[3][6], b[2][4] = a[4][7], b[2][5] = a[5][8], b[2][6] = a[6][8];//2
    b[3][1] = a[1][3], b[3][2] = a[2][4], b[3][3] = a[3][5], b[3][4] = a[4][6], b[3][5] = a[5][7], b[3][6] = a[6][7], b[3][7] = a[7][7];//3
    b[4][1] = a[1][2], b[4][2] = a[2][3], b[4][3] = a[3][4], b[4][4] = a[4][5], b[4][5] = a[5][6], b[4][6] = a[6][6], b[4][7] = a[7][6], b[4][8] = a[8][6];
    b[5][1] = a[1][1], b[5][2] = a[2][2], b[5][3] = a[3][3], b[5][4] = a[4][4], b[5][5] = a[5][5], b[5][6] = a[6][5], b[5][7] = a[7][5], b[5][8] = a[8][5], b[5][9] = a[9][5];
    b[6][1] = a[2][1], b[6][2] = a[3][2], b[6][3] = a[4][3], b[6][4] = a[5][4], b[6][5] = a[6][4], b[6][6] = a[7][4], b[6][7] = a[8][4], b[6][8] = a[9][4];
    b[7][1] = a[3][1], b[7][2] = a[4][2], b[7][3] = a[5][3], b[7][4] = a[6][3], b[7][5] = a[7][3], b[7][6] = a[8][3], b[7][7] = a[9][3];
    b[8][1] = a[4][1], b[8][2] = a[5][2], b[8][3] = a[6][2], b[8][4] = a[7][2], b[8][5] = a[8][2], b[8][6] = a[9][2];
    b[9][1] = a[5][1], b[9][2] = a[6][1], b[9][3] = a[7][1], b[9][4] = a[8][1], b[9][5] = a[9][1];
}

void createNode(numNode b[][10])
//创建二维数组
{
    for (int i = 1; i <= 9; i++)
        for (int j = 1; j <= 9; j++)
        {
            b[i][j].x = i;
            b[i][j].y = j;
        }
}

void lineDis(FILE* in, numNode b[][10]) {
    // 范式，1到9行的约束
    for (int p = 1; p <= 9; p++) {//1~9行
        int cf = p;
        if (p >= 6 && p <= 9) cf = 10 - p;
        //1，2，3，4，5，4，3，2，1

        // 必填数字
        for (int i = 5 - (cf - 1); i <= 5 + (cf - 1); i++) {
            for (int j = 1; j <= 5 + (cf - 1); j++)
                fprintf(in, "%d ", toSemanticEncoding(b[p][j].x, b[p][j].y, i, s));
            fprintf(in, "0\n");
        }

        //约束选填方案
        //8行的选1或9--1,9 
        //7行的四选2--1，2，8，9--12，28，89--1^2|2^8|8^9--(1|8)^(2|9)^(2|8)
        //6行6选3--1,2,3,7,8,9--123，237，378，789
        //5行7选4--1,2,3,4,6,7,8,9--1234,2346,3467,4678,6789
        for (int i = 1; i <= 4 - (cf - 1); i++) {
            for (int j = 6 + (cf - 1); j < 6 + (cf - 1) + i; j++) {
                for (int k = 1; k <= 5 + (cf - 1); k++)
                    fprintf(in, "%d ", toSemanticEncoding(b[p][k].x, b[p][k].y, i, s));
                for (int k = 1; k <= 5 + (cf - 1); k++)
                    fprintf(in, "%d ", toSemanticEncoding(b[p][k].x, b[p][k].y, j, s));
                fprintf(in, "0\n");
            }
        }

        // 每两格的数字不能重复
        for (int i = 1; i <= 9; i++)
            for (int j = 1; j <= 5 + (cf - 1); j++)
                for (int k = j + 1; k <= 5 + (cf - 1); k++)
                    fprintf(in, "-%d -%d 0\n", toSemanticEncoding(b[p][j].x, b[p][j].y, i, s), toSemanticEncoding(b[p][k].x, b[p][k].y, i, s));
    }
}

void ToCnf(int a[][9], int holes,char* cnf_filename) {
    //a[][]起始时00
    FILE* in = fopen(cnf_filename, "w");
    if (!in) {
        printf("Can't open this %s!\n",cnf_filename);
        return;
    }

    fprintf(in, "p cnf 549 %d\n", 5211 + 61 - holes);
    // 数独中所有的单子句

    //TODO:如何转化成连续编码？ 
    /*
    设i为行号，j为列号，k为填入的数字，那么我们可以将语义编码转换为自然顺序编码，公式如下：

    ijn → (L(i-1) + (j-1))*9 + n

    其中，L(i)表示第i行之前所有行的单元格总数。例如，对于第3行，L(3)=5+6=11。
    我们需要计算每一行前面所有行的单元格总数，这是因为每一行的单元格数量不同。我们在计算完每一行的单元格数量后，就可以通过这个公式将语义编码转换为自然顺序编码。*/


    //初始格局已存在的数字

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (a[i][j] != -1 && a[i][j] != 0) {
                fprintf(in, "%d 0\n", toSemanticEncoding(i + 1, j + 1, a[i][j], s));
            }
        }
    }
    Singularity(in);
    struct numNode bp[10][10], b[10][10];
    createNode(b);
    // 行约束
    lineDis(in, b);

    // 右对角线约束
    turnAnAngle(b, bp);
    lineDis(in, bp);

    // 左对角线约束
    turnAnAngle(b, bp);
    turnAnAngle(bp, b);
    lineDis(in, b);

    fclose(in);
}


void changeGrid(int hani[][9], int b[])
{
    for (int i = 0; i < 5; i++) hani[0][i] = b[i];
    for (int i = 5; i < 11; i++) hani[1][i - 5] = b[i];
    for (int i = 11; i < 18; i++) hani[2][i - 11] = b[i];
    for (int i = 18; i < 26; i++) hani[3][i - 18] = b[i];
    for (int i = 26; i < 35; i++) hani[4][i - 26] = b[i];
    for (int i = 35; i < 43; i++) hani[5][i - 35] = b[i];
    for (int i = 43; i < 50; i++) hani[6][i - 43] = b[i];
    for (int i = 50; i < 56; i++) hani[7][i - 50] = b[i];
    for (int i = 56; i < 61; i++) hani[8][i - 56] = b[i];

}
void to_1d(int hani[9][9], int b[]) {//hani纯语义编码
    for (int i = 0; i < 5; i++)b[i] =hani[0][i] ;
    for (int i = 5; i < 11; i++)  b[i]= hani[1][i - 5];
    for (int i = 11; i < 18; i++) b[i]= hani[2][i - 11];
    for (int i = 18; i < 26; i++) b[i]= hani[3][i - 18];
    for (int i = 26; i < 35; i++) b[i]= hani[4][i - 26];
    for (int i = 35; i < 43; i++) b[i]= hani[5][i - 35];
    for (int i = 43; i < 50; i++) b[i]= hani[6][i - 43];
    for (int i = 50; i < 56; i++) b[i]= hani[7][i - 50];
    for (int i = 56; i < 61; i++) b[i]= hani[8][i - 56];
}


void Singularity(FILE* in) {
    for (int p = 1; p <= 9; p++) {
        int cf = p;
        if (p >= 6 && p <= 9)cf = 10 - p;
        for (int j = 1; j <= 5 + (cf - 1); j++) {
            for (int k = 1; k <= 9; k++) {
                fprintf(in,"%d ", TransLiteral(100 * p + 10 * j + k));
            }
            fprintf(in,"0\n");
            for (int i = 1; i <= 9; i++) {
                for (int k = i + 1; k <= 9; k++) {
                    fprintf(in,"-%d -%d 0\n", TransLiteral(100 * p + 10 * j + i), TransLiteral(100 * p + 10 * j + k));
                }
            }
        }
    }
}