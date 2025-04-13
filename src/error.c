/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-24 09:40:32
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-29 13:35:45
 * @FilePath: /Lab/src/error.c
 * @Description: error read file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
//  #include "../include/CmmparserTypes.h"
 #include <stdio.h>
//  #include "../include/error.h"
//  #include <stdlib.h>
#include "../include/CmmparserTypes.h"
int has_error=0;
int error_line[10];
 void readError(int linenum,int issemanticValue){
    int i=0;
    while(i<10&&error_line[i]!=0){
        if (error_line[i]==linenum)
        {
            return;
        }
        i++;
    }
    error_line[i]=linenum;
    if (issemanticValue==0)
    {
        printf("\033[31mError B happens at line %d \033[0m\n",linenum);
    }
    else{
        printf("\033[31mError A happens at line %d \033[0m\n",linenum);
    }
 }

 void reporterror(int linenum,int errortype,char* error){
    printf("\033[31mError number %d happens at line %d ,the error is %s ;\033[0m\n",errortype,linenum,error);
 }