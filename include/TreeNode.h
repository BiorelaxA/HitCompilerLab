/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-23 19:50:38
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 16:47:53
 * @FilePath: /Lab/include/TreeNode.h
 * @Description: Treenode.h file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#ifndef TREENODE_H
#define TREENODE_H
#include <stdio.h>
#include "SemanticInfo.h"
struct TreeNode
{
    int token;       // 词法单元类型
    int linenum;     // 行号
    union {
        int intval;
        float floatval;
        char* ID;
        char* Type;
    };
    // 子节点相关字段
    struct TreeNode** children;  // 子节点指针数组
    int child_count;             // 当前子节点数量
    int capacity;                // 数组当前容量
    int issemanticValue;///用于判断是否为非终结符号
    //用于定义每个符号的语义
    SemanticInfo_ptr SemanticInfo;

};

typedef struct TreeNode* TreeNode_ptr;
typedef struct TreeNode TreeNode;
void p(int a);

typedef enum SyntaxToken_e{
    PROGRAM = 513,
    EXT_DEF_LIST = 514,
    EXT_DEF = 515,
    EXT_DEC_LIST = 516,
    SPECIFIER = 517,
    STRUCT_SPECIFIER = 518,
    OPT_TAG = 519,
    TAG = 520,
    VAR_DEC = 521,
    FUN_DEC = 522,
    VAR_LIST = 523,
    PARAM_DEC = 524,
    COMP_STM = 525,
    STMT_LIST = 526,
    STMT = 527,
    DEF_LIST = 528,
    DEF = 529,
    DEC_LIST = 530,
    DEC = 531,
    EXP = 532,
    ARGS = 533
}SyntaxToken;


TreeNode_ptr create_node(int token, int linenum,int child_count,int issamanticValue);
void add_children(TreeNode_ptr father,TreeNode_ptr child);
void set_root_node(TreeNode_ptr node);
const char* get_semantic_name(int token);
const char* get_token_name(int token);
void test_print(TreeNode_ptr node,int depth,FILE* output);
TreeNode_ptr getrootnode();
void free_tree(TreeNode_ptr node);
// void p(int a);
#endif  //TREENODE_H
