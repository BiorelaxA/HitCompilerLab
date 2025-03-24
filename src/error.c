/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-24 09:40:32
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-24 14:45:56
 * @FilePath: /Lab/src/error.c
 * @Description: error read file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
 #include "../include/TreeNode.h"
 #include <stdio.h>
 #include <stdlib.h>
 int has_error=0;
 int error_line[10];
 void readError(TreeNode_ptr error){
    int i=0;
    while(i<10&&error_line[i]!=0){
        if (error_line[i]==error->linenum)
        {
            return;
        }
        i++;
    }
    error_line[i]=error->linenum;
    if (error->issemanticValue==0)
    {
        printf("\033[31mError B happens at line %d \033[0m\n",error->linenum);
    }
    else{
        printf("\033[31mError A happens at line %d \033[0m\n",error->linenum);
    }
 }