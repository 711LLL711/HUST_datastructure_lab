#include "head.h"

int main()
{
    int op = 1;
  
    while (op!=0)
    {
        printf("1蜂窝数独求解\t\t\t2. SAT求解\n");
        printf("0.退出\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("数独求解\n");
            hanidoku();
            break;
        case 2:
            printf("SAT求解\n");
            Dpll_Display();
            break;
        case 0:
            printf("退出\n");
            break;
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
    }
}