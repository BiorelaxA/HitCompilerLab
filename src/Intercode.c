/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-04-12 22:09:12
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-13 12:47:36
 * @FilePath: /Lab/src/Intercode.c
 * @Description: Intercode tranlate
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include "../include/CmmparserTypes.h"
#include "../syntax.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



//不同与以往，这次不用传递了，本质不同了，这里是生成中间代码，1有问题都在词法，语法，语义检查了
void translate_Program(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_ExtDefList(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_ExtDef(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_ExtDecList(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_Specifier(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_StructSpecifier(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_opttag(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_tag(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_Var_Dec(TreeNode_ptr node ,IntercodeList_ptr intercodelist);
void translate_Fun_Dec(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_Var_List(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_ParamDec(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_CompStm(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_StmtList(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_Stmt(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_Def(TreeNode_ptr node,IntercodeList_ptr intercodelist);
void translate_DefList(TreeNode_ptr node,IntercodeList_ptr intercodelist);
//根据规约的产生式来选择tranlate的方式,这个函数将在add_children在bison规约时使用进行分析
void translate(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    
    switch (node->token)
    {
    case PROGRAM:
        translate_Program(node,intercodelist);
        break;
    case EXT_DEF_LIST:
        tranlate_ExtDefList(node,intercodelist);
        break;
    case EXT_DEF:
        trasnlate_ExtDef(node,intercodelist);
        break;
    case EXT_DEC_LIST:
        translate_ExtDecList( node, intercodelist);
        break;
    case SPECIFIER:
        translate_Specifier( node, intercodelist);
        break;
    case STRUCT_SPECIFIER:
        translate_StructSpecifier( node,intercodelist);
        break;
    case OPT_TAG:
        translate_opttag( node, intercodelist);
        break;
    case TAG:
        translate_tag( node, intercodelist);
        break;
    case VAR_DEC:
        translate_Var_Dec( node , intercodelist);
        break;
    case FUN_DEC:
        translate_Fun_Dec(node,intercodelist);
        break;
    case VAR_LIST:
        translate_Var_List( node, intercodelist);
        break;
    case PARAM_DEC:
        translate_ParamDec( node, intercodelist);
        break;
    case COMP_STM:
        translate_CompStm( node, intercodelist)
        break;
    case STMT_LIST:
        translate_StmtList( node, intercodelist);
        break;
    case STMT:
        translate_Stmt(node,intercodelist);
        break;
    case DEF_LIST:
        translate_DefList(node,intercodelist);
        break;
    case DEF:
        translate_Def(node,intercodelist);
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

void translate_Program(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //这里什么都不需要做，规约到这里已经是最后一部，不需要什么中间地址
}
/// @brief ExtDefList定义多个过程
/// @param node 父节点
void translate_ExtDefList(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //这里什么都不需要做，规约到这里已经是倒数第二步，不需要什么中间地址
}
/// @brief ExtDef定义的一个过程，或者一些宏定义
/// @param node 父节点
/// @param intercodelist 存储3地址码的动态数组
void translate_ExtDef(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //根据假设不存在函数声明，基本在这里会规约的产生式就2个ExtDecList SEMI(宏定义) / FunDec CompStm（定义函数）
    if (match_with_var(node,3,SPECIFIER,EXT_DEC_LIST,SEMI)==1)
    {
        //定义宏定义，这里必然已经加入了hashtable
        //由于假设也没有全局变量，这里不会使用的
        // return;

    }
    else if (match_with_var(node,3,SPECIFIER,FUN_DEC,COMP_STM)==1)
    {
        //这里可以全搬到FUN_DEC那里去，将函数插入符号表发生在FUN_DEC中,在语义分析是这里只是赋值了类型，这在三地址码中没有必要

        //定义了一个函数
        Intercode_ptr intercode=malloc(sizeof(Intercode));
        TreeNode_ptr children2=node->children[1];
        printf("[trasnlate_ExtDef]:def function %s\n",children2->SemanticInfo->name);
        char* func_name=children2->SemanticInfo->name;
        char function[8]="FUNCTION";
        intercode->kind=FUNCTION;
        intercode->content=strcat(function,func_name);
        printf("[trasnlate_ExtDef]:def function intercode is %s\n",intercode->content);
        //压入一个存储空间即可
        addIntercode(intercodelist,intercode);
        int param_count=node->SemanticInfo->semanticFunctioninfo->val_number;
        if (param_count>0)
        {
            //还需要参数
            char param[5]="PARAM";
            
            for (int i = 0; i < param_count; i++)
            {
                Intercode_ptr param=malloc(sizeof(Intercode));
                param->kind=PARAM;
                printf("[trasnlate_ExtDef] function param %s\n",node->SemanticInfo->semanticFunctioninfo->val_name[i]);
                param->content=strcat(param,node->SemanticInfo->semanticFunctioninfo->val_name[i]);
                addIntercode(intercodelist,param);
            }
        }
    }
    else{
        // return;
    }
    return;
}
/// @brief 这里应该是宏定义名，由于存在假设，这里也不需要考虑
/// @param node 
/// @param intercodelist 
void translate_ExtDecList(TreeNode_ptr node,IntercodeList_ptr intercodelist){
}
/// @brief 定义类型的，包括int,float,struct
/// @param node 规约的父节点
/// @param intercodelist 中间代码存储list
void translate_Specifier(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //这里是类型定义，也不需要考虑中间代码
}
/// @brief 这个structspecifier专门定义结构体
/// @param node 
/// @param intercodelist 
void translate_StructSpecifier(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    if (match_with_var(node,2,STRUCT,TAG)==1)
    {
        ///这里使用结构体,需要分批内存
        Intercode_ptr dec_mem=malloc(sizeof(Intercode));
        dec_mem->kind=DECMEM;
        char dec[3]="DEC";
        ///计算需要内存资源,tag为名字
        TreeNode_ptr children1=node->children[1];
        printf("[translate_StructSpecifier]:struct name is %s\n",children1->SemanticInfo->name);
        SemanticInfo_ptr p=hash_table_lookup(GLOBAL_HASH_TABLE,children1->SemanticInfo->name);
        int mem=0;
        if (p&&p->isstruct)
        {
            int entry_count=p->semanticmuldefinfo->type_count;
            for (int i = 0; i < entry_count; i++)
            {
                int var_count=p->semanticmuldefinfo->entries[i]->var_count;
                for (int j = 0; j < var_count; j++)
                {
                    if (p->semanticmuldefinfo->entries[i]->type==INT)
                    {
                        mem+=4;
                    }
                    else if (p->semanticmuldefinfo->entries[i]->type==FLOAT)
                    {
                        mem+=4;
                    }    
                    
                }
                
            }
            char num[20];
            sprintf(num,"%d",mem);
            dec_mem->content=strncat(dec,children1->SemanticInfo->name,num,3);
            printf("[translate_StructSpecifier]:%s\n",dec_mem->content);
        }
    }
    else if (node->child_count==5)
    {
        //这里定义结构体，这里不用管
    }
}
/// @brief opttag的使用适用于定义结构体名
/// @param node 
/// @param intercodelist 
void translate_opttag(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    ///不用生产3地址码
}
/// @brief Tag唯一用于使用结构体时需要结构体名
/// @param node 
/// @param intercodelist 
void translate_tag(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //不用生产3地址码
}
/// @brief 用于宏定义和函数的参数声明，这个也不用管3地址码
/// @param node 
/// @param intercodelist 
void translate_Var_Dec(TreeNode_ptr node ,IntercodeList_ptr intercodelist){
}

/// @brief 定义函数，但由于在Extdef已经生成三地址码了，这里不用生成
/// @param node 
/// @param intercodelist 
void translate_Fun_Dec(TreeNode_ptr node,IntercodeList_ptr intercodelist){
}
/// @brief 这个产生式产生函数参数定义
/// @param node 
/// @param intercodelist 
void translate_Var_List(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //也不用做什么
}
/// @brief 产生式g用于产生单一个函数参数
/// @param node 
/// @param intercodelist 
void translate_ParamDec(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //什么都不需要做
}
/// @brief 主要产生函数体，其中分为定义类型和各种表达式类型
/// @param node 
/// @param intercodelist 
void translate_CompStm(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    //这里什么都不需要做
}
/// @brief 用于产生不同表达式
/// @param node 
/// @param intercodelist 
void translate_StmtList(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    TreeNode_ptr node1=node->children[0];
    TreeNode_ptr node2=node->children[1];
    char go_to[4]="GOTO";
    char label[5]="LABEL";
    char linenum[10]=sprintf(label,"%d",node2->linenum);
    if (node1->SemanticInfo->intercode->kind==JUMP)
    {
        node1->SemanticInfo->intercode->content=strncat(go_to,label,linenum);
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=LABEL;
        in->content=strcat(label,linenum);
        addIntercode(intercodelist,in);
    }    
}
/// @brief 各种表达式
/// @param node 
/// @param intercodelist 
void translate_Stmt(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    if (match_with_var(node,2,EXP,SEMI)==1)
    {
        //赋值表达式，中间代码生成在exp做
    }
    else if (match_with_var(node,1,COMP_STM)==1)
    {
        //定义在函数体中重新定义一个过程，由于假设，不用管这个,不存在嵌套过程
    }
    else if (match_with_var(node,3,RETURN,EXP,SEMI)==1)
    {
        TreeNode_ptr node2=node2->children[1];
        char re[6]="RETURN";
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=RETURN;
        //exp如果是运算式呢，需要s找到计算运算式的中间变量
        ///如果exp只是一个id，那前面必然已经定义了，这里可以使用
        if (node2->SemanticInfo->isID==1)
        {
            //是变量，则寻找变量名，我们所有中间代码的变量名使用原有变量名，方便寻找
            printf("[translate_Stmt]:return var name is %s\n",node2->SemanticInfo->name);
            in->content=strcat(re,node2->SemanticInfo->name);
            addIntercode(intercodelist,in);
        }
        //todo这里需要exp内容来辨别到底是一个计算式子，还是单纯一个数字
        else if (node2->SemanticInfo->name==NULL)
        {
            if (node2->SemanticInfo->val_type==SVT_INT)
            {
                printf("[translate_Stmt]:return int %d\n",node2->intval);
                char int_val[20];
                sprintf(int_val,"%d",node2->intval);
                in->content=strcat(re,int_val);
                addIntercode(intercodelist,in);
            }
            else if (node2->SemanticInfo->val_type==SVT_FLOAT)
            {
                printf("[translate_Stmt]:return int %f\n",node2->floatval);
                char float_val[20];
                sprintf(float_val,"%f",node2->floatval);
                in->content=strcat(re,float_val);
                addIntercode(intercodelist,in);

            }
        }
    }
    else if (match_with_var(node,5,IF,LP,EXP,RP,STMT)==1)
    {
        //IF表达式,这里的exp大多是布尔表达式
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        TreeNode_ptr child1=node->children[2];
        TreeNode_ptr child2=node->children[4];
        char linenum[10];
        sprintf(linenum,"%d",child2->linenum);
        Intercode_ptr in=child1->SemanticInfo->intercode;
        Intercode_ptr ic=malloc(sizeof(Intercode));
        ic->kind=JUMP;
        //true goto stmt linenum
        ic->content=strncat(i_f,in->content,go_to,label,linenum,5);
        //if压入 true
        addIntercode(intercodelist,ic);
        //压入false ,将这个上传，唯有这个linenum不知
        Intercode_ptr false=malloc(sizeof(Intercode));
        false->kind=JUMP;
        false->content=strncat(go_to,label,"".3);
        addIntercode(intercodelist,false);
        //向上传递，由上面给出linenum
        node->SemanticInfo->intercode=false;

        Intercode_ptr la=malloc(sizeof(Intercode));
        la->kind=LABEL;
        la->content=strcat(label,linenum);
        addIntercode(intercodelist,la);
    }
    else if (node->child_count==7)
    {
        //todo顺序
        //if else if else 
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        TreeNode_ptr node1=node->children[2];
        TreeNode_ptr node2=node->children[4];
        TreeNode_ptr node3=node->children[6];
        //true
        Intercode_ptr true=malloc(sizeof(Intercode));
        true->kind=JUMP;
        char true_linenum[10];
        sprintf(true_linenum,"%d",node2->linenum);
        char false_linenum[10];
        sprintf(false_linenum,"%d",node3->linenum);
        true->content=strncat(i_f,node1->SemanticInfo->intercode->content,go_to,label,true_linenum,5);
        addIntercode(intercodelist,true);
        //false 
        Intercode_ptr false=malloc(sizeof(Intercode));
        false->kind=JUMP;
        false->content=strncat(go_to,label,false_linenum,3);
        addIntercode(intercodelist,false);
        //true label
        Intercode_ptr true_label=malloc(sizeof(Intercode));
        true_label->kind=LABEL;
        true_label->content=strcat(label,true_linenum);
        addIntercode(intercodelist,true_label);
        //goto next
        Intercode_ptr next=malloc(sizeof(Intercode));
        next->kind=JUMP;
        next->content=strncat(go_to,label,"",3);
        addIntercode(intercodelist,next);
        addIntercode(intercodelist,next);
        node->SemanticInfo->intercode=next;
        if (node2->SemanticInfo->intercode->kind==JUMP)
        {
            //补充上这个jump的label
            node2->SemanticInfo->intercode->content=next->content;
        }
        if (node3->SemanticInfo->intercode->kind==JUMP)
        {
            node3->SemanticInfo->intercode->content=next->content;
        }
    }
    else if (match_with_var(node,5,WHILE,LP,EXP,RP,STMT))
    {
        //while循环
        TreeNode_ptr node1=node->children[2];
        TreeNode_ptr node2=node->children[4];
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        char explinenum[10];
        char stmtlinenum[10];
        sprintf(explinenum,"%d",node1->linenum);
        sprintf(stmtlinenum,"%d",node2->linenum);
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=LABEL;
        in1->content=strcat(label,explinenum);
        addIntercode(intercodelist,in1);
        //true
        Intercode_ptr in2 =malloc(sizeof(Intercode));
        in2->kind=JUMP;
        in2->content=strncat(i_f,node1->SemanticInfo->intercode->content,go_to,label,stmtlinenum,5);
        addIntercode(intercodelist,in2);
        //false
        Intercode_ptr in3 =malloc(sizeof(Intercode));
        in3->kind=JUMP;
        in3->content=strncat(go_to,label,"",3);
        node->SemanticInfo->intercode=in3;
        addIntercode(intercodelist,in2);

        //true label
        Intercode_ptr in4 =malloc(sizeof(Intercode));
        in4->kind=LABEL;
        in4->content=strcat(label,stmtlinenum);
        addIntercode(intercodelist,in4);

        //go back to while exp
        Intercode_ptr in5 =malloc(sizeof(Intercode));
        in5->kind=JUMP;
        in5->content=strncat(go_to,label,explinenum);
        addIntercode(intercodelist,in5);
    }
    // else
    // {
        
    // }
}
/// @brief 这个产生式用于产生1多个变量定义
/// @param node 
/// @param intercodelist 
void translate_DefList(TreeNode_ptr node,IntercodeList_ptr intercodelist){

}
/// @brief 产生一个定义
/// @param node 
/// @param intercodelist 
void translate_Def(TreeNode_ptr node,IntercodeList_ptr intercodelist){

}
/// @brief 产生多个变量
/// @param node 
/// @param intercodelist 
void translate_DecList(TreeNode_ptr node,IntercodeList_ptr intercodelist){

}
/// @brief 产生一个变量
/// @param node 
/// @param intercodelist 
void translate_Dec(TreeNode_ptr node,IntercodeList_ptr intercodelist){

}

/// @brief 各种计算式
/// @param node 
/// @param intercodelist 
void translate_Exp(TreeNode_ptr node,IntercodeList_ptr intercodelist){
    if (match_with_var(node,3,EXP,ASSIGNOP,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,AND,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,OR,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,EQ,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,NEQ,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,LT,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,LE,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,GT,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,GE,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,PLUS,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,MINUS,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,STAR,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,DIV,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,LP,EXP,RP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,2,MINUS,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,2,NOT,EXP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,4,ID,LP,ARGS,RP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,ID,LP,RP)==1)
    {
        /* code */
    }
    else if (match_with_var(node,4,EXP,LB,EXP,RB)==1)
    {
        /* code */
    }
    else if (match_with_var(node,3,EXP,DOT,ID)==1)
    {
        /* code */
    }
    else if (match_with_var(node,1,ID)==1)
    {
        /* code */
    }
    else if (match_with_var(node,1,INT)==1)
    {
        /* code */
    }
    else if (match_with_var(node,1,FLOAT)==1)
    {
        /* code */

    }
    else{

    }
}












// 初始化动态数组
void initIntercodeList(IntercodeList *list, int initialCapacity) {
    list->codes = (Intercode_ptr*)malloc(sizeof(Intercode_ptr) * initialCapacity);
    list->size = 0;
    list->capacity = initialCapacity;
}

// 添加中间代码到数组
void addIntercode(IntercodeList *list, Intercode_ptr code) {
    if (list->size >= list->capacity) {
        // 动态扩容（通常按2倍策略）
        list->capacity *= 2;
        list->codes = (Intercode_ptr*)realloc(list->codes, sizeof(Intercode_ptr) * list->capacity);
    }
    list->codes[list->size++] = code;
}

// 释放内存
void freeIntercodeList(IntercodeList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->codes[i]->content);  // 释放字符串内存
        free(list->codes[i]);           // 释放Intercode结构体内存
    }
    free(list->codes);                  // 释放数组内存
    list->size = 0;
    list->capacity = 0;
}