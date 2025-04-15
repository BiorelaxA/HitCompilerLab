/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 17:36:44
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-15 16:03:58
 * @FilePath: /Lab/lab2.c
 * @Description: lab2 main file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include <stdio.h>
#include "include/CmmparserTypes.h"
#include <string.h>
#include <limits.h>
#include "syntax.tab.h"
#include "lex.yy.c"

// extern YYTOKENTYPE;
extern int yylex(void); // 添加 yylex 的函数声明
extern void yyrestart(FILE* input_file);
extern FILE* yyin;
// const int PATH_MAX=100;
FILE* create_for_output(const char* filename);
HashTable_ptr GLOBAL_HASH_TABLE = NULL;
StringStack_ptr Function_Stack=NULL;


int main(int argc, char const *argv[])
{
    GLOBAL_HASH_TABLE=create_hash_table(95);
    Function_Stack=create_stack(10);

    ///建立一个hashtable全局共享
    if (argc<2)
    {
        printf("Usage: use scanner with a file along:./scanner file\n");
        return 1;
    }
    // create_for_output(argv[1]);
    FILE* f=fopen(argv[1],"r");
    FILE* output=create_for_output(argv[1]);
    if (!f)
    {
        perror(argv[1]);
        return 1;
    }
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
        // test_print(getrootnode(),0,output);
        free_tree(getrootnode());
        return 0;
    }
    destroy_hash_table(GLOBAL_HASH_TABLE);
    destroy_stack(Function_Stack);
}
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
    char output_path[100];
    int ret = snprintf(output_path, sizeof(output_path), "%s%s", output_dir, filename_part);
    if (ret < 0 || ret >= (int)sizeof(output_path)) {
        return NULL; // 路径过长，处理失败
    }

    // 创建并打开文件
    FILE *fp = fopen(output_path, "w");
    return fp;
}
