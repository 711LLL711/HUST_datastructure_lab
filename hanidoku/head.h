#ifndef HEAD_H
#define HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#pragma warning(disable:4996)
#define OK 1
#define ERROR 0
#define FOUND 1
#define NOTFOUND 0
#define NOANSWER 0
#define YES 1
#define NO 0
#define PATH_SIZE 1024      // 路径字符串大小
#define EPOCH 5             // 重复运行次数
typedef int status;
typedef struct LiteralNode
{
    int data;
    struct LiteralNode* right;
} LiteralNode;//文字节点

typedef struct ClauseNode
{
    struct LiteralNode* right;
    struct ClauseNode* down;//指向下一个子句
} ClauseNode;//子句节点

typedef struct numNode { //为翻转提供准备
    int x;
    int y;
} numNode;


//全局变量
int literal_num;

void Dpll_Display();
char* ChooseExample();
int choose(ClauseNode* LIST, int varnum);
int choose2(ClauseNode* LIST);
status DpllSolver(ClauseNode* s, int* truth_table, int optimize);
ClauseNode* CnfParser(int* literal_num, char* filename, int init);
status GetPInfo(char buff[], int* literal_num, int* clause_num, FILE* fp);
ClauseNode* ReadClauses(char* buff, FILE* fp, int* var_num, int clause_num);
ClauseNode* CreateClauseUnit(char* buff, FILE* fp);
LiteralNode* CreateLiteralUnit(char* buff);
void DestroyAllClause(ClauseNode* head);

void hanidoku();
void solvehanidoku(char* cnf_filename, int hani[9][9]);


void outfile(char* filename, int suc, int literal_num, int table[], clock_t time);
void ToCnf(int a[][9], int holes, char* cnf_filename);
void print(const int a[]);
void changeGrid(int hani[][9], int b[]);
void to_1d(int hani[9][9], int b[]);
void createHanidoku(int a[], char* filename);
void createStartinggrid(int a[], int b[], int holes);
void turnAnAngle(numNode a[][10], numNode b[][10]);
void createNode(numNode b[][10]);
void lineDis(FILE* in, numNode b[][10]);

void toDirectEncoding(int n, int* row, int* col, int* number);
int TransLiteral(int x);
void Singularity(FILE* in);
void inputans(int a[9][9]);
void usersolve(int origin[9][9], int correctarr[9][9], int correct1d[61]);
int choose3(ClauseNode* LIST);
#endif