#include "head.h"

int main()
{
    int op = 1;
  
    while (op!=0)
    {
        printf("1�����������\t\t\t2. SAT���\n");
        printf("0.�˳�\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("�������\n");
            hanidoku();
            break;
        case 2:
            printf("SAT���\n");
            Dpll_Display();
            break;
        case 0:
            printf("�˳�\n");
            break;
        default:
            printf("�����������������\n");
            break;
        }
    }
}