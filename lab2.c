/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 17:36:44
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 20:36:41
 * @FilePath: /Lab/lab2.c
 * @Description: lab2 main file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include <stdio.h>
#include <stdlib.h>
#include "include/error.h"
#include "include/HashTable.h"
#include "include/SemanticInfo.h"
#include "include/TreeNode.h"
#include "lab2.h"




int main(int argc, char const *argv[])
{
    ///建立一个hashtable全局共享
    GLOBAL_HASH_TABLE=create_hash_table(60);
}
