/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 16:16:31
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-28 18:22:51
 * @FilePath: /Lab/src/SemanticInfo.c
 * @Description: file to definit semantic information
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

#include "include/SemanticInfo.h"
#include "include/TreeNode.h"
#include "include/HashTable.h"
#include "include/error.h"
#include "../syntax.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include "lab2.h"
#include <stdarg.h>
#include "../syntax.tab.h"


/// @brief 为每个节点创建一个语义属性
/// @param type_id 文法符号id，用于后续在hashtable中映射
/// @param issemanticValue 是否为终结符
/// @return semanticinfo 指针
SemanticInfo_ptr create_semanticinfo(TreeNode_ptr node){
    SemanticInfo_ptr s=malloc(sizeof(SemanticInfo));
    s->issemanticValue=node->issemanticValue;
    s->Type_id=node->token;


    s->name=NULL;
    s->isfunction=0;
    s->isstruct=0;
    s->isArray=0;
    s->val_type=SVT_VOID;
    s->semanticarrayinfo=NULL;
    s->semanticFunctioninfo=NULL;
    s->semanticstructinfo=NULL;
    s->isdefined=0;
    s->isID=0;
    // ///todo,应该还要将属性加入到hashtable中
    // if (issemanticValue==1)
    // {
    //     hash_table_insert(GLOBAL_HASH_TABLE,s);
    // }
    // return s;
}

void SetHashTable(HashNode_ptr hashtable,TreeNode_ptr node){
    
    
}      

void SetHashTable_Specifier(HashNode_ptr hashtable,TreeNode_ptr node){
    if (node->child_count!=1)
    {
        return;
    }
    TreeNode_ptr child=node->children[0];
    if (child->token==TYPE)
    {
        node->SemanticInfo->val_type=(child->token==INT)?SVT_INT:SVT_FLOAT;
    }
    else if (node->children[0]->token==STRUCT_SPECIFIER)
    {
        node->SemanticInfo->val_type=SVT_STRUCT;
    }
}

void SetHashTable_FunDec(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==4)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child3=node->children[2];
        TreeNode_ptr child4=node->children[3];
        node->SemanticInfo->isfunction=1;
        node->SemanticInfo->name=child1->ID;
        //如果是规约的话，作为e综合属性，Varlist应当已经拿到了
        SemanticFunctionInfo_ptr f=
        //todo 需要varlist的number
        return;
    }
    else if (node->child_count==3)
    {
        if (match_with_var(node,3,ID,LP,RP))
        {
            TreeNode_ptr child1=node->children[0];
            TreeNode_ptr child2=node->children[1];
            TreeNode_ptr child3=node->children[2];
            node->SemanticInfo->isfunction=1;
            node->SemanticInfo->name=child1->ID;
            node->SemanticInfo->semanticFunctioninfo=NULL;
        }
        // else if (match_with_var(node,3,ID,LP,VAR_LIST))
        // {
            
        // }
        else
        {
            return;
        }
    }
    else{
        return;
    } 
}

void SetHashTable_Exp(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        TreeNode_ptr child=node->children[0];
        if (child->token==INT)
        {
            node->SemanticInfo->val_type=SVT_INT;
        }
        else if (child->token==SVT_FLOAT)
        {
            node->SemanticInfo->val_type=SVT_FLOAT;
        }
        else
        {
            node->SemanticInfo=hash_table_lookup(hashtable,child->ID);
            if (node->SemanticInfo==NULL)
            {
                reporterror(node->linenum,UndefinedVariable,"can not use undefined variable");
            }
            
        }
    }
    else if (node->child_count==2)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        if (match_with_var(node,2,MINUS,EXP))
        {
            node->SemanticInfo=child2->SemanticInfo;
        }
        else if (match_with_var(node,2,NOT,EXP))
        {
            node->SemanticInfo=child2->SemanticInfo;   
        }
    }
    
    else if (node->child_count==3)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child3=node->children[2];
        if (match_with_var(node,3,EXP,ASSIGNOP,EXP))
        {
            ///赋值语句基本只能给变量赋值，所以地一个node必然是从id规约过来的
            if (child1->isID)
            {
                if (child1->SemanticInfo->val_type!=child3->SemanticInfo->val_type)
                {
                    reporterror(node->linenum,AssignmentTypeMismatch,"assignment type don`t match");
                }
                else
                {
                    ///仅仅是赋值变化了数值
                    node->SemanticInfo=child1->SemanticInfo;
                }
            }
            else
            {
                reporterror(node->linenum,AssignmentTypeMismatch,"assignment can only assign to a varible");
            }
        }
        else if (match_with_var(node,3,EXP,AND,EXP))
        {
            //这里思考如下：
            //首先如果2个均是数值，那就比较是否可以直接计算
            //如果其中存在id变量，此时需要查找hashtalbe,需要注意，基于LR分析为最左规约，每次寻找最左直接短语规约，必然，如果变量有定义，那么就要
            //会在hashtable中存在，反之，可以说明使用了未定义的变量，如果存在，必然拥有对应的type,则可以比较是否存在type不一致问题

            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }  
        else if (match_with_var(node,3,EXP,OR,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,EQ,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,NEQ,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,LT,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,LE,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,GT,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,GE,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,PLUS,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,MINUS,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,STAR,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,DIV,EXP))
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,LP,EXP,RP))
        {
            node->SemanticInfo->val_type=child2->SemanticInfo->val_type;
        }
        else if (match_with_var(node,3,EXP,DOT,ID))
        {
            ///这个时候说明是结构体访问
            if (!child1->SemanticInfo->isstruct)
            {
                reporterror(node->linum,UndefinedStruct,"Member access on non-struct");
            }
            else if (child1->SemanticInfo->isstruct)
            {
                ///访问的变量部队
                int flag=0;
                SemanticStructInfo_ptr p=child1->SemanticInfo->semanticstructinfo;
                int number=p->val_number;
                for(int i=0;i<number;i++){
                    if (p->val_name[i]==child3->ID)
                    {
                        flag=1;
                        break;
                    }
                }
                if (flag){}
                else
                {
                    reporterror(node->linenum,UndefinedStructMember,"can not find struct member")
                }
            } 
        } 
    }   
    // else if (node->child_count=4)
    // {
    //     if (match_with_var(node,4,ID,LP.ARGS,RP))
    //     {

    //     }
    //     else if (match_with_var(node,4,EXP,LB,EXP,RB))
    //     {
            
    //     }
    // }
    return;
}


void SetHashTable_ExtDef(HashNode_ptr hashtable,TreeNode_ptr node){
    
    
}




















////怎么把语义联合起来
////现在考虑的是通过每次create一个node同时定义起语义并检查，检查时机？观察所有可能出现问题的地方检查，按照错误类型猜测？
////决定按照先建立树，在建立树的过程中计算语义，analyze应当在树建立之后解决，这个时候符号表也已经建立好了
void Analyze_Program(TreeNode_ptr root){
    //Program->ExtDefList一个产生式,必然Program的语义和ExtDefList没什么区别，直接分析ExtDefList
    if (root->child_count==0)
    {
        return;
    }
    else{
        TreeNode_ptr node=root->children[0];
        Analyze_ExtDefList(node);
    }
}
void Analyze_ExtDefList(TreeNode_ptr node){
    //ExtDefList表示0个或多个ExtDef,而每个ExtDef表示一个全局变量，函数，结构体等
    if (node->child_count==2)
    {
        //ExtDefList->ExtDef ExtDefList 产生大量的定义等
        TreeNode_ptr ExtDef_node=node->children[0];
        Analyze_ExtDef(ExtDef_node);
        TreeNode_ptr ExtDefList_node=node->children[1];
        Analyze_ExtDefList(ExtDefList_node);
    }
    else if (node->child_count==0)
    {
        //意味这程序中什么都没有
        printf("[warning]:the program is a none file");
        return;
    }
    else{
        return;
    }
}
void Analyze_ExtDef(TreeNode_ptr node){
    if (node->child_count==3)
    {
        if (match_with_var(node,3,SPECIFIER,EXT_DEC_LIST,SEMI))
        {
            //ExtDef->Specifier ExtDecList SEMI,定义int a,b,c
            //在这里检查是否重复定义？下移
            
        }
        else if (match_with_var(node,3,SPECIFIER,FUN_DEC,COMP_STM))
        {
            
        }
        else if (match_with_var(node,3,SPECIFIER,FUN_DEC,SEMI))
        {
            
        }
        else{
            return;
        }
    }
    else if (node->child_count==2)
    {
        if (match_with_var(node,2,SPECIFIER,SEMI))
        {
            /* code */
        }
        else if (match_with_var(node,2,SPECIFIER,EXT_DEC_LIST))
        {
            /* code */
        }
        else if (match_with_var(node,2,SPECIFIER,FUN_DEC))
        {
            /* code */
        }
        else{
            return;
        }
    }
    else if (node->child_count==1)
    {
        if (match_with_var(node,1,SPECIFIER))
        {
            
        }
        else
        {
            return;
        }
    }
    else{
        return;
    }
}
void Analyze_Specifier(TreeNode_ptr node){
    if (node->child_count==1)
    {
        if (match_with_var(node,1,TYPE))
        {
            /* code */
        }
        else if (match_with_var(node,STRUCT_SPECIFIER))
        {
            /* code */
        }
        else{
            return;
        }
        
    }
    else{
        return;
    }
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

//注意参数传递顺序应当与产生式一致
int match_with_var(TreeNode_ptr node,int child_num,...){
    va_list args;
    int flag=1;
    va_start(args,child_num);
    for (int i=0;i<child_num,i++){
        int arg=va_arg(args,int);
        flag=(node->children[i]->token==arg)?1:0;
    }
    va_end(args);
    return flag;
}
///这个函数用于检查运算中的类型一致，变量是否定义，变量运算中类型是否一致
///node1,node2i分布为参与运算的2个node
int check_on_logic_caculate(HashTable_ptr hashtable,TreeNode_ptr father,TreeNode_ptr node1,TreeNode_ptr node2){
    if (node1->SemanticInfo->isID==0&&node2->SemanticInfo->isID==0)
    {
        //只是数值运算
        if (node1->SemanticInfo->val_type!=node2->SemanticInfo->val_type)
        {
            reporterror(father->linenum,OperatorTypeMismatch,"error value type,can not use different type to caculate");
            return 0;
        }
        else{
            return 1;
        }
    }
    else if (node1->SemanticInfo->name!=NULL&&node2->SemanticInfo->name==NULL)
    {
        SemanticInfo_ptr p=hash_table_lookup(hashtable,node1->SemanticInfo->name);
        if (p==NULL)
        {
            reporterror(father->linenum,UndefinedVariable,"error undefined variable,can not use undefined variable to caculate");  
            return 0;
        }
        else
        {
            if (p->val_type!=node2->SemanticInfo->val_type)
            {
                reporterror(father->linenum,OperatorTypeMismatch,"error value type,can not use different type to caculate");  
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else if (node1->SemanticInfo->name==NULL&&node2->SemanticInfo->name!=NULL)
    {
        SemanticInfo_ptr p=hash_table_lookup(hashtable,node2->SemanticInfo->name);
        if (p==NULL)
        {
            reporterror(father->linenum,UndefinedVariable,"error undefined variable,can not use undefined variable to caculate");  
            return 0;
        }
        else
        {
            if (p->val_type!=node2->SemanticInfo->val_type)
            {
                reporterror(father->linenum,OperatorTypeMismatch,"error value type,can not use different type to caculate");  
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else if (node1->SemanticInfo->name!=NULL&&node2->SemanticInfo->name!=NULL)
    {
        SemanticInfo_ptr p1=hash_table_lookup(hashtable,node1->SemanticInfo->name);
        SemanticInfo_ptr p2=hash_table_lookup(hashtable,node2->SemanticInfo->name);
        if (p1==NULL||p2==NULL)
        {
            reporterror(father->linenum,UndefinedVariable,"error undefined variable,can not use undefined variable to caculate");  
            return 0;
        }
        else
        {
            if (p1->val_type!=p2->val_type)
            {
                reporterror(father->linenum,OperatorTypeMismatch,"error value type,can not use different type to caculate");  
                return 0;
            }
            else{
                return 1;
            }
        }
    }
    else
    {
        return 0;
    }
    
    
    
}