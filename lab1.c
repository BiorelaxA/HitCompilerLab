/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-23 11:37:03
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-25 18:39:05
 * @FilePath: /Lab/lab1.c
 * @Description: main file for lab1
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include <stdlib.h>
#include<stdint.h>
#include <stdio.h>
#include "include/TreeNode.h"
#include "syntax.tab.h"
#include "include/error.h"
#include <string.h>
extern int yylex(void); // 添加 yylex 的函数声明
extern void yyrestart(FILE* input_file);
extern FILE* yyin;
const int PATH_MAX=100;
// #define YYDEBUG 1
FILE* create_for_output(const char* filepath);
int main(int argc, char const *argv[])
{
    // printf("fdfdfse\n");
    if (argc<2)
    {
       //no file in args
       printf("Usage: use scanner with a file along:./scanner file\n");
       return 1;
    }
    // printf("%s",argv[1]);
    create_for_output(argv[1]);
    FILE* f=fopen(argv[1],"r");
    FILE* output=create_for_output(argv[1]);
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
    // printf("456");
    yyrestart(f);
    // yydebug=1;
    yyparse();
    // printf("123");
    if (has_error==1)
    {
        free_tree(getrootnode());
        return 0;
    }
    else{
        test_print(getrootnode(),0,output);
        free_tree(getrootnode());
        return 0;
    }

}


#include <stdio.h>
#include <string.h>
#include <limits.h>

FILE* create_for_output(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }

    // 指定的输出路径，假设输出目录存在且以斜杠结尾
    const char *output_dir = "/home/shy/CompilerPrinciple/Lab/test/Lab1_test/output/";
    
    // 提取文件名部分
    const char *filename_part = strrchr(filename, '/');
    if (filename_part != NULL) {
        filename_part++; // 跳过斜杠
    } else {
        filename_part = filename; // 无斜杠，直接使用整个字符串
    }

    // 检查文件名是否有效
    if (strlen(filename_part) == 0) {
        return NULL;
    }

    // 构建输出路径
    char output_path[PATH_MAX];
    int ret = snprintf(output_path, sizeof(output_path), "%s%s", output_dir, filename_part);
    if (ret < 0 || ret >= (int)sizeof(output_path)) {
        return NULL; // 路径过长，处理失败
    }

    // 创建并打开文件
    FILE *fp = fopen(output_path, "w");
    return fp;
}
