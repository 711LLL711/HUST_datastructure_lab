#include "head.h"
void outfile(char* filename,int suc,int literal_num,int table[],clock_t time) {
	//输出文件名，成功状态，文字个数，真值表
	 // 提取文件名部分
	const char* cnf_position = strstr(filename, ".cnf");

	if (cnf_position == NULL) {
		printf("文件名格式错误\n");
		return;
	}

	// 计算文件名的长度
	size_t basename_length = cnf_position - filename;

	// 创建新的 .res 文件名
	char* res_filename = (char*)malloc(basename_length + 5); // 5 是 ".res\0" 的长度

	if (res_filename == NULL) {
		printf("Memory allocation failed");
		exit(1);
	}

	strncpy(res_filename, filename, basename_length);
	res_filename[basename_length] = '\0'; // 确保以 null 结尾
	strcat(res_filename, ".res");

	printf("%s", res_filename);
	FILE* fp = fopen(res_filename, "w");
	if (fp == NULL) {
		printf("求解结果保存失败\n");
		exit(1);
	}
	if (suc) {
		fprintf(fp, "s 1\n");//1表示成功
		fprintf(fp, "v ");
		for (int i = 0; i < literal_num; i++) {
			if (table[i] == 0) {
				fprintf(fp,"-%d ", i+1);
			}
			else if(table[i]==1) {
				fprintf(fp,"%d ", i+1);
			}
		}
		fprintf(fp, "\nt %d ms\n", time);
	}
	else {
		fprintf(fp, "s 0\n");
		fprintf(fp, "v \n");
		fprintf(fp, "t %d ms\n", time);
	}
	printf("求解结果保存成功\n");
	free(res_filename);
	fclose(fp);
}