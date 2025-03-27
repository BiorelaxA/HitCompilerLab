/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 16:16:31
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 17:09:40
 * @FilePath: /Lab/src/SemanticInfo.c
 * @Description: file to definit semantic information
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

#include "include/SemanticInfo.h"
#include "include/TreeNode.h"
#include <stdlib.h>
#include <stdio.h>


/// @brief 为每个节点创建一个语义属性
/// @param type_id 文法符号id，用于后续在hashtable中映射
/// @param name 文法name
/// @return semanticinfo 指针
SemanticInfo_ptr create_semanticinfo(int type_id,char* name){
    SemanticInfo_ptr s=malloc(sizeof(SemanticInfo));
    s->name=name;
    s->Type_id=type_id;
    ///todo,应该还要将属性加入到hashtable中
    return s;
}


//语义分析

/// @brief 每次规约时进行分析
/// @param father 
void SemanticAnalyzer(TreeNode_ptr father){
    //todo 基本想法是match father的token,然后调用分析
    //todo 每个定义
    switch (father->token)
    {
    case PROGRAM: 
        break;
    case EXT_DEF_LIST:
        break;
    case EXT_DEF:
        break;
    case EXT_DEC_LIST:
        break;
    case SPECIFIER:
        break;
    case OPT_TAG:
        break;
    case TAG:
        break;
    case VAR_DEC:
        break;
    case FUN_DEC:
        break;
    case VAR_LIST:
        break;
    case PARAM_DEC:
        break;
    case COMP_STM:
        break;
    case STMT_LIST:
        break;
    case STMT:
        break;
    case DEF_LIST:
        break;
    case DEF:
        break;
    case DEC_LIST:
        break;
    case DEC:
        break;
    case EXP:
        break;
    case ARGS:
        break;
    default:
        break;
    }


}



