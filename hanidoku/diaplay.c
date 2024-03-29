#include "head.h"
//�����ɵķ�������cnf�ļ�
void solvehanidoku(char* cnf_filename,int hani[9][9]) {
    int result, i;

    char filename[PATH_SIZE];
    strcpy(filename, cnf_filename);
    ClauseNode* s = CnfParser(&literal_num, filename, 0);//����cnf�ļ����ṹ��

    int* truth_table = (int*)malloc(literal_num * sizeof(int));  // ��ֵ��
    if (truth_table == NULL) {
        printf("��ֵ�������ڴ�ʧ��");
    }
    for (i = 0; i < literal_num; i++) {
        truth_table[i] = 1;
    }
    result = DpllSolver(s, truth_table, 1);
    //����ֵ�����������������
    if (result) {
        printf("���ɹ���\n");
        int resultarr[61] = { 0 };
        int k = 0;
        for (i = 0; i < literal_num; i++) {
            if (truth_table[i] == 1) {

                //printf("%d\n", i + 1);
                int row=0, col=0, number=0;
                toDirectEncoding(i + 1, &row, &col, &number);
                if (k < 61) {
                    resultarr[k++] = number;
                }
                else {
                    printf("resultarr����������");
                    exit(1);
                }

                hani[row][col] = number;//�������
            }
        }
        printf("��ֵ��Ԫ���У�%d \n", k);

        //����--��ӡ���ɽ����hani
       /* for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9 - abs(5 - i); j++) {
                printf("%d ", hani[i][j]);
            }
            printf("\n");
        }*/
       /* for (i = 0; i < 61; i++) {
            printf("%d ", b[i]);
        }*/
        //to_1d(hani, b);//ת����һά����

        print(resultarr);//��ӡ��������
    }
    else {
        printf("�޽�");
    }
    
    DestroyAllClause(s);
    free(truth_table);
}

void Dpll_Display() {
    int result, i;
    char filename[PATH_SIZE];
    clock_t t, t1, t2;// ��ʱ��
    ClauseNode* s;// �Ӿ伯
    clock_t isoptimize[2] = { 0 };
 
    int op = 1;
    while (op != 0) {
        printf("1.��ʼ���cnf�ļ� 0.�˳�SAT���\n");
        printf("���������ѡ��\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            strcpy(filename, ChooseExample());                        // ���·��
            CnfParser(&literal_num, filename, 1);                     // �Ȼ��������������1�����ǳ�ʼ��
            //printf("literal_num:%d", literal_num);
            int* truth_table = (int*)malloc(literal_num * sizeof(int));  // ��ֵ��
            if (truth_table == NULL) {
                printf("��ֵ�������ڴ�ʧ��");
            }
            for (i = 0; i < literal_num; i++) {
                truth_table[i] = 1;
            }// ��ʼ����ֵ������ѳ�ʼֵ��Ϊ1��Ҳ�ɸ�Ϊ0

            printf("\n    ������,���ظ�����%d��ȡƽ��ֵ...\n\n", EPOCH);

            //�ظ�����EPOCH�� ȡƽ��ֵ
            for (int optimize = 0; optimize <= 1; optimize++) {
                t = t1 = t2 = 0; // ��ʼ����ʱ��
                for (i = 0; i < EPOCH; i++)
                {
                    t = clock();
                    s = CnfParser(&literal_num, filename, 0);
                    t1 += clock() - t;
                    result = DpllSolver(s, truth_table, optimize);
                    t2 += clock() - t;
                    //��������
                    DestroyAllClause(s);
                }
                isoptimize[optimize] = t2 / EPOCH;
                // ������
                if (optimize) {
                    printf("�Ż���\n");
                }
                else {
                    printf("�Ż�ǰ: \n");
                }
                printf("���غ�ʱ��%ldms\n", t1 / EPOCH);           // ȡƽ��ʱ��
                printf("����ʱ��%ldms\n", t2 / EPOCH - t1 / EPOCH);
                printf("�ܺ�ʱ  ��%ldms\n\n", t2 / EPOCH);

            }
            if (result)
            {
                printf("    ������Ӿ伯�����㣬һ�������:\n");   // �н�
                printf("    ��Ϊ��");                              // ��ӡ��ֵΪ1�ı�Ԫ
                for (int k = 0; k < literal_num; k++)    if (truth_table[k])  printf("%d ", k + 1);
                printf("\n");
            }
            else    printf("    ������Ӿ伯�������㣡\n");        // �޽�
            printf("optimized by %lf", (1.0 * isoptimize[0] - isoptimize[1]) / isoptimize[0]);
            outfile(filename, result, literal_num, truth_table, isoptimize[1]);//������ļ�
            free(truth_table);
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("��������ȷ���֣�");
            break;
        }
    }
}

char* ChooseExample()
{
    int op = 0;
    char filename[4][50] = { "./case/sud00009.cnf","./case/ais10.cnf","./case/sat-20.cnf", "./case/unsat-5cnf-30.cnf" };
    printf("\n1.���ܲ��� sud00009  2.���ܲ��� ais10\n");
    printf("3.���ܲ��� sat20     4.���ܲ��� unsat-5\n");
    printf("0.��������\n");
    printf("��������Ҫ���������[0-4]��");
    while (1)
    {
        scanf("%d", &op);
        if (op == 1)         return  "./case/sud00009.cnf";
        else if (op == 2)    return "./case/ais10.cnf";
        else if (op == 3)    return "./case/sat-20.cnf";
        else if (op == 4)    return "./case/unsat-5cnf-30.cnf";
        else if (op == 0) {
            printf("�����룺");
            static char filename[PATH_SIZE];
            scanf("%s", filename);
            return filename;
        }
        else {
            printf("����������:");
        }

    }
}

void hanidoku() {
//��������ģ��
    int a[61], b[61], holes, hani[9][9], correctans[9][9];
    memset(hani, -1, sizeof(hani));
    memset(correctans, -1, sizeof(correctans));
    int op = 1,op2=1;
    char origin_filename[] = "./hanidoku.txt";//��ʼ�������
    while (op != 0) {
        printf("1.��ʼ�������� 0. �˳���������\n");
        scanf("%d", &op);
        if (op == 1) {
            memset(hani, -1, sizeof(hani));
            printf("��������\n�������ڶ�����\n");
            scanf("%d", &holes);
            createHanidoku(a, origin_filename);//��ʼ�����ļ�txt����
            print(a);

            changeGrid(correctans, a);//������ȷ����������

            createStartinggrid(a, b, holes);//�ڶ�������ʼ���
            //һά���飬��0��ʼ
            printf("���ɳ�ʼ������֣�\n");
            print(b);

            changeGrid(hani, b);//һά����ת��Ϊ��ά����,hani��[0][0]��ʼ

            //����cnf�ļ���
            const char* cnf_position = strstr(origin_filename, ".txt");
            if (cnf_position == NULL) {
                printf("�ļ�����ʽ����\n");
                return;
            }
            // �����ļ����ĳ���
            size_t basename_length = cnf_position - origin_filename;

            // �����µ� .cnf �ļ���
            char* cnf_filename = (char*)malloc(basename_length + 5); // 5 �� ".cnf\0" �ĳ���
            if (cnf_filename == NULL) {
                printf("Memory allocation failed");
                exit(1);
            }
            strncpy(cnf_filename, origin_filename, basename_length);
            cnf_filename[basename_length] = '\0'; // ȷ���� null ��β
            strcat(cnf_filename, ".cnf");

            //��Լ��cnf�ļ�
            ToCnf(hani, holes, cnf_filename);//hani��9*9��ά���飬ת����cnf�ļ�ʱ����-��-���洢��Ԫ
            printf("�ѹ�Լ����cnf�ļ�%s\n", cnf_filename);

            while (op2 != 0) {
                printf("1.������Ĵ� 2. ���� 0.�˳����\n");
                scanf("%d", &op2);
                switch (op2)
                {
                case 1:
                    usersolve(hani, correctans, a);
                    break;
                case 2:
                    solvehanidoku(cnf_filename, hani);
                    break;
                default:
                    break;
                }
            }
          
        }
    }
}


void usersolve(int origin[9][9], int correctarr[9][9], int correct1d[61]) {

    inputans(origin);
   
    //checkans�ȶԴ��������Ƿ���ȷ
    int i, j;
    int iscorrect = 1;
    char c;
   
    printf("�ȶԴ�\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - abs(4 - i); j++) {
            if (origin[i][j] != correctarr[i][j]) {
                printf("row:%d col:%d, origin:%d,correct:%d\n", i+1, j+1, origin[i][j],correctarr[i][j]);
                iscorrect = 0;
            }
        }
    }
    if (iscorrect) {
        printf("�����ȷ��\n");
    }else {
        printf("������\n");
        getchar();
        printf("�Ƿ�鿴��ȷ�𰸣�y/n\n");
        scanf("%c", &c);
        if (c == 'y' || c == 'Y') {
            print(correct1d);
            getchar();
        }
    }
    return;
}