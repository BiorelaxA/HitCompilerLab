#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/CmmparserTypes.h"
#include "../syntax.tab.h"
// #include "../include/HashTable.h"
// #include "../include/SemanticInfo.h"
#include <stdarg.h>
// #include "../lab2.h"
// #include "../include/CmmparserTypes.h"

char GrammarSymbolNames[ARGS - PROGRAM + 1][20] = {
    "Program",
    "ExtDefList",
    "ExtDef",
    "ExtDecList",
    "Specifier",
    "StructSpecifier",
    "OptTag",
    "Tag",
    "VarDec",
    "FunDec",
    "VarList",
    "ParamDec",
    "CompSt",
    "StmtList",
    "Stmt",
    "DefList",
    "Def",
    "DecList",
    "Dec",
    "Exp",
    "Args"
};
char TokenNames[WHILE - INT + 1][20] = {
    "INT",
    "FLOAT",
    "ID",
    "SEMI",
    "COMMA",
    "ASSIGNOP",
    "RELOP",
    "RELOP",
    "RELOP",
    "RELOP",
    "RELOP",
    "RELOP",
    "PLUS",
    "MINUS",
    "STAR",
    "DIV",
    "AND",
    "OR",
    "DOT",
    "NOT",
    "TYPE",
    "LP",
    "RP",
    "LB",
    "RB",
    "LC",
    "RC",
    "STRUCT",
    "RETURN",
    "IF",
    "ELSE",
    "WHILE"
};
extern char* yytext;
TreeNode_ptr root=NULL;
/// @brief 用于创建树中节点，token是文法符号的属性，由于basion为LALR统一采用综合属性 linum为节点所在位置
TreeNode_ptr create_node(int token, int linenum, int child_count, int issemanticValue) {
    TreeNode_ptr node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation failed in create_node\n");
        exit(EXIT_FAILURE);
    }
    node->token = token;
    node->linenum = linenum;
    node->ID = NULL;
    node->intval = 0;
    node->floatval = 0.0f;
    node->children = NULL;
    node->child_count = 0;
    node->issemanticValue = issemanticValue;

    switch (token) {
        case ID:
            if (yytext != NULL) {
                node->ID = strdup(yytext);
            }
            break;
        case INT:
            if (yytext != NULL) {
                node->intval = atoi(yytext);
            }
            break;
        case FLOAT:
            if (yytext != NULL) {
                node->floatval = strtof(yytext, NULL);
            }
            break;
        case TYPE:
            if (yytext!=NULL)
            {
                node->Type=strdup(yytext);
            }
            
        default:
            break;
    }

    if (child_count > 0) {
        node->children = malloc(child_count * sizeof(TreeNode_ptr));
        if (node->children == NULL) {
            fprintf(stderr, "Memory allocation failed for children in create_node\n");
            exit(EXIT_FAILURE);
        }
        node->child_count = 0;
    }
    node->SemanticInfo=create_semanticinfo(node->issemanticValue,node->token);
    return node;
}
// void add_children(TreeNode_ptr father,TreeNode_ptr child){
//     father->children[father->child_count]=child;
//     father->child_count++;
// }

void add_children(TreeNode_ptr father,int childnum,...) {
    va_list args;
    va_start(args,childnum);
    for(int i=0;i<childnum;i++){
        TreeNode_ptr child=va_arg(args,TreeNode_ptr);
        if (father == NULL || child == NULL) {
            fprintf(stderr, "Invalid argument in add_children\n");
            return;
        }
        if (father->children == NULL) {
            fprintf(stderr, "Children array not initialized in add_children\n");
            return;
        }
        // printf("[add_child]:%d\n",child->token);
        father->children[father->child_count] = child;
        father->child_count++;
    }
    #ifdef LAB2_ENABLE_HASH
    SetHashTable(GLOBAL_HASH_TABLE, father);
    #endif
    //这里继续使用条件编译，启动中间代码生成
    va_end(args);
}

void set_root_node(TreeNode_ptr node){
    root=node;
}

const char* get_name(int token,int issemantic){
    if (issemantic)
    {
        return get_semantic_name(token);
    }
    else{
        return get_token_name(token);
    }
    
}

const char* get_semantic_name(int token){
   return GrammarSymbolNames[token-PROGRAM];
}
const char* get_token_name(int token){
    return TokenNames[token-INT];
}
TreeNode_ptr getrootnode(){
    return root;
}

/// @brief 先序遍历树
/// @param root 根节点
void test_print(TreeNode_ptr node,int depth,FILE* f){
    // printf("[TEST_PRINT]:%d\n",node->token);
    // printf("[TEST_PRINT]:%d\n",node->children[0]->token);
    if (node==NULL)
    {
        return;
    }
    int child_number=node->child_count;
    int i=0;
    // printf("[test_print]:%d\n",node->issemanticValue);
    ///空串
    for(int i = 0; i < depth; i++)
    {
        fprintf(f,"    ");
    }
    if (node->issemanticValue==0){
        fprintf(f,"%s (%d)\n",get_semantic_name(node->token),node->linenum);
    }
    else{
        // printf("f12312\n");
        switch(node->token)
        {
            case ID:
                fprintf(f,"ID: %s\n", node->ID);
                break;
            case TYPE:
                fprintf(f,"TYPE: %s\n", node->ID);
                break;
            case INT:
                fprintf(f,"INT: %d\n", node->intval);
                break;
            case FLOAT:
                fprintf(f,"FLOAT: %f\n", node->floatval);
                break;
            case GE:
                fprintf(f,"RELOP\n" );
                break;
            default:
                fprintf(f,"%s\n", get_token_name(node->token));
                break;
        }
    }
    if (child_number==0)
    {
        return;
    }
    
    while (i<child_number)
    {
        test_print(node->children[i],depth+1,f);
        i+=1;
    }
}
/// @brief 递归释放树节点及其子节点
void free_tree(TreeNode_ptr node) {
    if (node == NULL) return;

    // 释放子节点
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }

    // 释放字符串资源（ID、TYPE）
    switch (node->token) {
        case ID:
        case TYPE:
            free(node->ID);  // 确保 ID 是通过 strdup 分配的
            break;
        default:
            break;
    }

    // 释放 children 数组
    free(node->children);
    // 释放节点自身
    free(node);
}

// void p(int a){
//     printf("hello");
//     //only print the used function
//     printf("this is root %d",a);
// }













