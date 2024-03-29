#include "head.h"
//解生成的蜂窝数独cnf文件
void solvehanidoku(char* cnf_filename,int hani[9][9]) {
    int result, i;

    char filename[PATH_SIZE];
    strcpy(filename, cnf_filename);
    ClauseNode* s = CnfParser(&literal_num, filename, 0);//解析cnf文件到结构体

    int* truth_table = (int*)malloc(literal_num * sizeof(int));  // 真值表
    if (truth_table == NULL) {
        printf("真值表申请内存失败");
    }
    for (i = 0; i < literal_num; i++) {
        truth_table[i] = 1;
    }
    result = DpllSolver(s, truth_table, 1);
    //把真值表解析出蜂窝数独答案
    if (result) {
        printf("求解成功！\n");
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
                    printf("resultarr数组已满！");
                    exit(1);
                }

                hani[row][col] = number;//语义编码
            }
        }
        printf("真值变元共有：%d \n", k);

        //测试--打印生成结果的hani
       /* for (i = 1; i <= 9; i++) {
            for (j = 1; j <= 9 - abs(5 - i); j++) {
                printf("%d ", hani[i][j]);
            }
            printf("\n");
        }*/
       /* for (i = 0; i < 61; i++) {
            printf("%d ", b[i]);
        }*/
        //to_1d(hani, b);//转化成一维数组

        print(resultarr);//打印蜂窝数独
    }
    else {
        printf("无解");
    }
    
    DestroyAllClause(s);
    free(truth_table);
}

void Dpll_Display() {
    int result, i;
    char filename[PATH_SIZE];
    clock_t t, t1, t2;// 计时器
    ClauseNode* s;// 子句集
    clock_t isoptimize[2] = { 0 };
 
    int op = 1;
    while (op != 0) {
        printf("1.开始求解cnf文件 0.退出SAT求解\n");
        printf("请输入你的选择：\n");
        scanf("%d", &op);
        switch (op) {
        case 1:
            strcpy(filename, ChooseExample());                        // 获得路径
            CnfParser(&literal_num, filename, 1);                     // 先获得文字数，最后的1表明是初始化
            //printf("literal_num:%d", literal_num);
            int* truth_table = (int*)malloc(literal_num * sizeof(int));  // 真值表
            if (truth_table == NULL) {
                printf("真值表申请内存失败");
            }
            for (i = 0; i < literal_num; i++) {
                truth_table[i] = 1;
            }// 初始化真值表，这里把初始值设为1，也可改为0

            printf("\n    计算中,将重复计算%d次取平均值...\n\n", EPOCH);

            //重复计算EPOCH次 取平均值
            for (int optimize = 0; optimize <= 1; optimize++) {
                t = t1 = t2 = 0; // 初始化计时器
                for (i = 0; i < EPOCH; i++)
                {
                    t = clock();
                    s = CnfParser(&literal_num, filename, 0);
                    t1 += clock() - t;
                    result = DpllSolver(s, truth_table, optimize);
                    t2 += clock() - t;
                    //销毁链表
                    DestroyAllClause(s);
                }
                isoptimize[optimize] = t2 / EPOCH;
                // 输出结果
                if (optimize) {
                    printf("优化后：\n");
                }
                else {
                    printf("优化前: \n");
                }
                printf("加载耗时：%ldms\n", t1 / EPOCH);           // 取平均时间
                printf("求解耗时：%ldms\n", t2 / EPOCH - t1 / EPOCH);
                printf("总耗时  ：%ldms\n\n", t2 / EPOCH);

            }
            if (result)
            {
                printf("    结果：子句集可满足，一组解如下:\n");   // 有解
                printf("    解为：");                              // 打印真值为1的变元
                for (int k = 0; k < literal_num; k++)    if (truth_table[k])  printf("%d ", k + 1);
                printf("\n");
            }
            else    printf("    结果：子句集不可满足！\n");        // 无解
            printf("optimized by %lf", (1.0 * isoptimize[0] - isoptimize[1]) / isoptimize[0]);
            outfile(filename, result, literal_num, truth_table, isoptimize[1]);//输出答案文件
            free(truth_table);
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("请输入正确数字！");
            break;
        }
    }
}

char* ChooseExample()
{
    int op = 0;
    char filename[4][50] = { "./case/sud00009.cnf","./case/ais10.cnf","./case/sat-20.cnf", "./case/unsat-5cnf-30.cnf" };
    printf("\n1.性能测试 sud00009  2.性能测试 ais10\n");
    printf("3.功能测试 sat20     4.功能测试 unsat-5\n");
    printf("0.自行输入\n");
    printf("请输入需要计算的算例[0-4]：");
    while (1)
    {
        scanf("%d", &op);
        if (op == 1)         return  "./case/sud00009.cnf";
        else if (op == 2)    return "./case/ais10.cnf";
        else if (op == 3)    return "./case/sat-20.cnf";
        else if (op == 4)    return "./case/unsat-5cnf-30.cnf";
        else if (op == 0) {
            printf("请输入：");
            static char filename[PATH_SIZE];
            scanf("%s", filename);
            return filename;
        }
        else {
            printf("请重新输入:");
        }

    }
}

void hanidoku() {
//蜂窝数独模块
    int a[61], b[61], holes, hani[9][9], correctans[9][9];
    memset(hani, -1, sizeof(hani));
    memset(correctans, -1, sizeof(correctans));
    int op = 1,op2=1;
    char origin_filename[] = "./hanidoku.txt";//初始完整格局
    while (op != 0) {
        printf("1.开始蜂窝数独 0. 退出蜂窝数独\n");
        scanf("%d", &op);
        if (op == 1) {
            memset(hani, -1, sizeof(hani));
            printf("蜂窝数独\n请输入挖洞数：\n");
            scanf("%d", &holes);
            createHanidoku(a, origin_filename);//初始满足文件txt类型
            print(a);

            changeGrid(correctans, a);//存入正确的数独终盘

            createStartinggrid(a, b, holes);//挖洞创建初始格局
            //一维数组，从0开始
            printf("生成初始数独格局：\n");
            print(b);

            changeGrid(hani, b);//一维数组转化为二维数组,hani从[0][0]起始

            //生成cnf文件名
            const char* cnf_position = strstr(origin_filename, ".txt");
            if (cnf_position == NULL) {
                printf("文件名格式错误\n");
                return;
            }
            // 计算文件名的长度
            size_t basename_length = cnf_position - origin_filename;

            // 创建新的 .cnf 文件名
            char* cnf_filename = (char*)malloc(basename_length + 5); // 5 是 ".cnf\0" 的长度
            if (cnf_filename == NULL) {
                printf("Memory allocation failed");
                exit(1);
            }
            strncpy(cnf_filename, origin_filename, basename_length);
            cnf_filename[basename_length] = '\0'; // 确保以 null 结尾
            strcat(cnf_filename, ".cnf");

            //规约成cnf文件
            ToCnf(hani, holes, cnf_filename);//hani是9*9二维数组，转化成cnf文件时用行-列-数存储变元
            printf("已规约生成cnf文件%s\n", cnf_filename);

            while (op2 != 0) {
                printf("1.输入你的答案 2. 求解答案 0.退出求解\n");
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
   
    //checkans比对答案数组检查是否正确
    int i, j;
    int iscorrect = 1;
    char c;
   
    printf("比对答案\n");
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9 - abs(4 - i); j++) {
            if (origin[i][j] != correctarr[i][j]) {
                printf("row:%d col:%d, origin:%d,correct:%d\n", i+1, j+1, origin[i][j],correctarr[i][j]);
                iscorrect = 0;
            }
        }
    }
    if (iscorrect) {
        printf("解答正确！\n");
    }else {
        printf("解答错误！\n");
        getchar();
        printf("是否查看正确答案？y/n\n");
        scanf("%c", &c);
        if (c == 'y' || c == 'Y') {
            print(correct1d);
            getchar();
        }
    }
    return;
}