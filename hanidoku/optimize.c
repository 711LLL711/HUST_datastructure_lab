#include "head.h"
#define CLAUSENUM 5000
//优化变元选取策略对DPLL进行优化
//最大活动子句（Maximum Activity Clause）策略
struct times {
    int data;
    int count;
    int Positive;
    int Negative;
};

//降序排列
int cmp(const void* a, const void* b) {
    const struct times* structA = (const struct times*)a;
    const struct times* structB = (const struct times*)b;
    return structB->count - structA->count;
}


int choose(ClauseNode* LIST, int varnum) {
    ClauseNode* head = LIST;
    struct times *record=(struct times*)malloc(varnum * sizeof(struct times));
    int i;
    for (i = 0; i < varnum; i++) {
        record[i].data = 0;
        record[i].count = 0;
        record[i].Positive = 0;
        record[i].Negative = 0;
    }
     int k = 0,j=0;

    for (head = head->down; head != NULL; head = head->down) {//逐子句
        LiteralNode* literal = head->right;
        for (; literal != NULL; literal = literal->right) {//逐文字
            for (j = 0;j < k; j++) {//搜索record中已经是否有该文字
                if (record[j].data == abs(literal->data)) {
                    break;
                }
            }
            record[j].data = abs(literal->data);
            record[j].count++;
            if (literal->data > 0) {
                record[j].Positive++;
            }else {
                record[j].Negative++;
            }
            if (j == k)k++;
        }
    }
    //排序
    qsort(record, k, sizeof(struct times), cmp);
    //选变元
    if (record[0].Positive > record[0].Negative) {
        return record[0].data;
    }
    else {
        return 0 - record[0].data;
    }
    free(record);
}
//最短子句优先原则
int compare2(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
int choose2(ClauseNode* LIST) {
    ClauseNode* head = LIST;
    LiteralNode* literal = NULL;
    int min = 10000;
    ClauseNode* minindex=NULL;
    int count[CLAUSENUM]={0}, k = 0;
    for (head = LIST->down; head != NULL; head = head->down) {
        for (literal = head->right; literal != NULL; literal = literal->right) {
            count[k]++;
        }//子句长度
        if (count[k] < min) {
            min = count[k];
            minindex = head;
        }
        k++;
    }
    return minindex->right->data;
}

int choose3(ClauseNode* LIST) {
    ClauseNode* head = LIST;
    LiteralNode* literal = NULL;
    int *count = (int *)malloc(literal_num*sizeof(int));

    // Count the occurrence of each variable
    for (head = LIST->down; head != NULL; head = head->down) {
        for (literal = head->right; literal != NULL; literal = literal->right) {
            count[abs(literal->data)]++;  // Use the absolute value of data as the variable can be positive/negative
        }
    }

    // Find the variable with maximum occurrence
    int max = 0;
    for (int i = 0; i < literal_num; i++) {
        if (count[i] > count[max]) {
            max = i;
        }
    }

    return max;
}