/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-04-12 22:09:12
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-15 16:00:16
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
#include <stdarg.h>

#define MAX_SIZE 1000
int global_next[MAX_SIZE];

// void translate(TreeNode_ptr node);
//不同与以往，这次不用传递了，本质不同了，这里是生成中间代码，1有问题都在词法，语法，语义检查了
void translate_Program(TreeNode_ptr node);
void translate_ExtDefList(TreeNode_ptr node);
void translate_ExtDef(TreeNode_ptr node);
void translate_ExtDecList(TreeNode_ptr node);
void translate_Specifier(TreeNode_ptr node);
void translate_StructSpecifier(TreeNode_ptr node);
void translate_opttag(TreeNode_ptr node);
void translate_tag(TreeNode_ptr node);
void translate_Var_Dec(TreeNode_ptr node );
void translate_Fun_Dec(TreeNode_ptr node);
void translate_Var_List(TreeNode_ptr node);
void translate_ParamDec(TreeNode_ptr node);
void translate_CompStm(TreeNode_ptr node);
void translate_StmtList(TreeNode_ptr node);
void translate_Stmt(TreeNode_ptr node);
void translate_Def(TreeNode_ptr node);
void translate_DefList(TreeNode_ptr node);
void translate_DecList(TreeNode_ptr node);
void translate_Dec(TreeNode_ptr node);
void translate_Exp(TreeNode_ptr node);
void translate_Args(TreeNode_ptr node);
int alloc_label_number();
char* replace_next_with_int(const char* original, int num);
//void addIntercode(IntercodeList_ptr list, Intercode_ptr code);
// char* split_before_colon(const char* str);
char* new_temp();
// char* insert_before_first_newline(const char* original, const char* insert_str);

Intercode_ptr new_Intercode_ptr(){
    Intercode_ptr ptr=malloc(sizeof(Intercode));
    ptr->kind=RAW;
    ptr->isprint=0;
    ptr->isneednext=0;
    return ptr;
}



// char* concat(int n, ...); 
//根据规约的产生式来选择tranlate的方式,这个函数将在add_children在bison规约时使用进行分析
void translate(TreeNode_ptr node){
    
    switch (node->token)
    {
    case PROGRAM:
        translate_Program(node);
        break;
    case EXT_DEF_LIST:
        translate_ExtDefList(node);
        break;
    case EXT_DEF:
        translate_ExtDef(node);
        break;
    case EXT_DEC_LIST:
        translate_ExtDecList( node);
        break;
    case SPECIFIER:
        translate_Specifier( node);
        break;
    case STRUCT_SPECIFIER:
        translate_StructSpecifier( node);
        break;
    case OPT_TAG:
        translate_opttag( node);
        break;
    case TAG:
        translate_tag( node);
        break;
    case VAR_DEC:
        translate_Var_Dec( node );
        break;
    case FUN_DEC:
        translate_Fun_Dec(node);
        break;
    case VAR_LIST:
        translate_Var_List( node);
        break;
    case PARAM_DEC:
        translate_ParamDec( node);
        break;
    case COMP_STM:
        translate_CompStm( node);
        break;
    case STMT_LIST:
        translate_StmtList( node);
        break;
    case STMT:
        translate_Stmt(node);
        break;
    case DEF_LIST:
        translate_DefList(node);
        break;
    case DEF:
        translate_Def(node);
        break;
    case DEC_LIST:
        translate_DecList(node);
        break;
    case DEC:
        translate_Dec(node);
        break;
    case EXP:
        translate_Exp(node);
        break;
    case ARGS:
        translate_Args(node);
        break;
    default:
        break;
    }
}

void translate_Program(TreeNode_ptr node){
    //这里什么都不需要做，规约到这里已经是最后一部，不需要什么中间地址
}
/// @brief ExtDefList定义多个过程
/// @param node 父节点
void translate_ExtDefList(TreeNode_ptr node){
    //这里什么都不需要做，规约到这里已经是倒数第二步，不需要什么中间地址
}
/// @brief ExtDef定义的一个过程，或者一些宏定义
/// @param node 父节点
/// @param intercodelist 存储3地址码的动态数组
void translate_ExtDef(TreeNode_ptr node){
        //根据假设不存在函数声明，基本在这里会规约的产生式就2个ExtDecList SEMI(宏定义) / FunDec CompStm（定义函数）
    // if (match_with_var(node,3,SPECIFIER,EXT_DEC_LIST,SEMI)==1)
    // {
        //定义宏定义，这里必然已经加入了hashtable
        //由于假设也没有全局变量，这里不会使用的
        // return;

    // }
    // else if (match_with_var(node,3,SPECIFIER,FUN_DEC,COMP_STM)==1)
    // {
        //这里可以全搬到FUN_DEC那里去，将函数插入符号表发生在FUN_DEC中,在语义分析是这里只是赋值了类型，这在三地址码中没有必要

        //定义了一个函数
        // Intercode_ptr intercode = malloc(sizeof(Intercode));
        // TreeNode_ptr children2 = node->children[1];
        // printf("[translate_ExtDef]:def function %s\n", children2->SemanticInfo->name);
        // char* func_name = children2->SemanticInfo->name;
        // intercode->kind = FUNCTION;
        
        // // 安全地拼接字符串
        // size_t len = strlen("FUNCTION") + strlen(func_name) + 1;
        // intercode->content = malloc(len);
        // if (intercode->content) {
        //     snprintf(intercode->content, len, "FUNCTION%s", func_name);
        //     printf("[translate_ExtDef]:def function intercode is %s\n", intercode->content);
        //     node->SemanticInfo->intercode=intercode;
        //     //addIntercode(intercodelist, intercode);
        // }
        
        // //压入一个存储空间即可
        // //addIntercode(intercodelist,intercode);
        // int param_count=0;
        // if (!children2->SemanticInfo->semanticFunctioninfo)
        // {
            
        // }else{
        //     param_count=children2->SemanticInfo->semanticFunctioninfo->val_number;
        // }
        
        // if (param_count>0)
        // {
        //     //还需要参数
        //     char pa[5]="PARAM";
        //     Intercode_ptr param=malloc(sizeof(Intercode));
        //     param->kind=PARAM;
        //     param->content=malloc(50*sizeof(char));
        //     param->content=pa;
        //     for (int i = 0; i < param_count; i++)
        //     {
        //          param->content=strcat(param->content,children2->SemanticInfo->semanticFunctioninfo->val_name[i]);
        //     }
        //     printf("[trasnlate_ExtDef] function param %s\n",param->content);
        //     //addIntercode(intercodelist,param);
        // }
    // }
}
/// @brief 这里应该是宏定义名，由于存在假设，这里也不需要考虑
/// @param node 
/// @param intercodelist 
void translate_ExtDecList(TreeNode_ptr node){
}
/// @brief 定义类型的，包括int,float,struct
/// @param node 规约的父节点
/// @param intercodelist 中间代码存储list
void translate_Specifier(TreeNode_ptr node){
    //这里是类型定义，也不需要考虑中间代码
    // node->->intercode=NULL;
}
/// @brief 这个structspecifier专门定义结构体
/// @param node 
/// @param intercodelist 
void translate_StructSpecifier(TreeNode_ptr node){
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
            // dec_mem->content=concat(3,dec,children1->SemanticInfo->name,num);
            sprintf(dec_mem->content,"%s\t%s\t%s\n",dec,children1->SemanticInfo->name,num);
            // node->SemanticInfo->intercode=dec_mem;
            dec_mem->isprint=1;
            children1->intercode=dec_mem;
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
void translate_opttag(TreeNode_ptr node){
    ///不用生产3地址码
}
/// @brief Tag唯一用于使用结构体时需要结构体名
/// @param node 
/// @param intercodelist 
void translate_tag(TreeNode_ptr node){
    //不用生产3地址码
}
/// @brief 用于宏定义和函数的参数声明，这个也不用管3地址码
/// @param node 
/// @param intercodelist 
void translate_Var_Dec(TreeNode_ptr node ){
}

/// @brief 定义函数，但由于在Extdef已经生成三地址码了，这里不用生成
/// @param node 
/// @param intercodelist 
void translate_Fun_Dec(TreeNode_ptr node){
    Intercode_ptr intercode = malloc(sizeof(Intercode));
    TreeNode_ptr child = node->children[0];
    printf("[translate_ExtDef]:def function %s\n", child->ID);
    char* func_name = child->ID;
    intercode->kind = FUNCTION;
    
    // 安全地拼接字符串
    size_t len = strlen("FUNCTION") + strlen(func_name) + 1;
    intercode->content = malloc(len);
    intercode->isprint=1;
    if (intercode->content) {
        sprintf(intercode->content,"%s %s %s\n","FUNCTION",child->ID,":");
        printf("[translate_ExtDef]:def function intercode is %s\n", intercode->content);
        // node->SemanticInfo->intercode=intercode;
        // node->SemanticInfo->intercode->isprint=0;
        //addIntercode(intercodelist, intercode);
        // if (node->child_count==3)
        // {
        //     /* code */
        //     node->children[2]->intercode=intercode;
        // }
        // else if (node->child_count==4)
        // {
        //     node->children[3]->intercode=intercode;
        // }
        node->children[1]->intercode=intercode;
        
        
    }
}
/// @brief 这个产生式产生函数参数定义
/// @param node 
/// @param intercodelist 
void translate_Var_List(TreeNode_ptr node){
}
/// @brief 产生式g用于产生单一个函数参数
/// @param node 
/// @param intercodelist 
void translate_ParamDec(TreeNode_ptr node){
    if (node->child_count==2)
    {
        //Specifier VarDec
        TreeNode_ptr child=node->children[1];
        ///这里应该还需要处理多个参数的内容，这里todo
        //处理插入到hashtable中，将临时变量插入到hashtable中todo
        Intercode_ptr in=malloc(sizeof(Intercode));
        char* temp=new_temp();
        in->kind=PARAM;
        in->isprint=1;
        in->content=malloc(50*sizeof(char));
        sprintf(in->content,"%s %s\n","PARAM",temp);
        in->res=temp;
        SemanticInfo_ptr p=hash_table_lookup(GLOBAL_HASH_TABLE,child->SemanticInfo->name);
        if (p)
        {
            p->temp=malloc(50*sizeof(char));
            p->temp=temp;
        }
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in;
        add_children(node,1,new_node);
    }
    
}
/// @brief 主要产生函数体，其中分为定义类型和各种表达式类型
/// @param node 
/// @param intercodelist 
void translate_CompStm(TreeNode_ptr node){
    //这里什么都不需要做
}
/// @brief 用于产生不同表达式
/// @param node 
/// @param intercodelist 
void translate_StmtList(TreeNode_ptr node){
    //Stmt StmtList 
    TreeNode_ptr node1=node->children[0];
    TreeNode_ptr node2=node->children[1];
    if (node1->next)
    {
        int labelnum=alloc_label_number();
        int i=0;
        while (node1->next[i]>0)
        {
            global_next[node1->next[i]]=labelnum;
            i++;
        }
        // sprintf(node1->intercode->next,"%d",labelnum);
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=LABEL;
        in->content=malloc(50*sizeof(char));
        in->isprint=1;
        sprintf(in->content,"%s %s%d %s\n","LABEL","label",labelnum,":");
        node2->intercode=in;
    }
}
/// @brief 各种表达式
/// @param node 
/// @param intercodelist 
void translate_Stmt(TreeNode_ptr node){
    if (match_with_var(node,2,EXP,SEMI)==1)
    {
        TreeNode_ptr child=node->children[0];
        node->intercode=malloc(sizeof(Intercode));
    }
    else if (match_with_var(node,1,COMP_STM)==1)
    {
        //定义在函数体中重新定义一个过程，由于假设，不用管这个,不存在嵌套过程
    }
    else if (match_with_var(node,3,RETURN,EXP,SEMI)==1)
    {
        TreeNode_ptr node2=node->children[1];
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=SVT_RETURN;
        in->isprint=1;
        in->content=malloc(50*sizeof(char));
        sprintf(in->content,"%s %s\n","RETURN",node2->intercode->res);
        TreeNode_ptr node3=node->children[2];
        node3->intercode=in;
    }
    else if (match_with_var(node,5,IF,LP,EXP,RP,STMT)==1)
    {
        //IF表达式,这里的exp大多是布尔表达式
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="label";
        char LABEL[5]="LABEL";
        TreeNode_ptr node1=node->children[2];
        TreeNode_ptr node3=node->children[3];
        TreeNode_ptr node2=node->children[4];
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->next=get_new_nextlinenumber();
        node->intercode=in1;
        node->next=malloc(50*sizeof(int));
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=JUMP;
        in->isprint=1;
        in->content=malloc(50*sizeof(char));
        int labelnum1=alloc_label_number();
        if (node2->next==NULL)
        {
            //stmt没有next要求
            in->next=in1->next;
            node2->intercode->next=in1->next;
            node->next[0]=in->next;
            node->next[1]=node2->intercode->next;
            node->next[2]=in1->next;
        }
        sprintf(in->content,"%s %s %s %s%d\n%s %s%s\n%s %s%d %s\n",i_f,node1->intercode->content,go_to,label,labelnum1,go_to,label,"next",LABEL,label,labelnum1,":");
        node3->intercode=in;
    }
    else if (node->child_count==7)
    {
        //IF LP Exp RP Stmt ELSE Stmt  
        char i_f[] = "IF";      // 自动推断长度（3）
        char go_to[] = "GOTO";  // 自动推断长度（5）
        char label[] = "label"; // 自动推断长度（6）
        char LABEL[] = "LABEL"; // 自动推断长度（6）
        TreeNode_ptr node1=node->children[2];
        TreeNode_ptr node2=node->children[4];
        TreeNode_ptr node3=node->children[6];
        TreeNode_ptr node4=node->children[3];
        TreeNode_ptr node5=node->children[5];
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->next=get_new_nextlinenumber();
        node->intercode=in3;
        node->next=malloc(50*sizeof(int));
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=JUMP;
        in1->content=malloc(50*sizeof(char));
        in1->isprint=1;
        int c=alloc_label_number();
        int labelnum1=alloc_label_number();
        int labelnum2=alloc_label_number();
        sprintf(in1->content,"%s %s %s %s%d\n%s %s%d\n%s %s%d %s\n",i_f,node1->intercode->content,go_to,label,labelnum1,go_to,label,labelnum2,LABEL,label,labelnum1,":");
        node4->intercode=in1;
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=JUMP;
        in2->isprint=1;
        in2->content=malloc(50*sizeof(char));
        node2->intercode->next=in3->next;
        in2->next=in3->next;
        //todo,这里只做了else的数组合并应该还有if的
        if (node3->next)
        {
            //合并二者
            node->next=node3->next;
            int i=0;
            while (node->next[i]>0)
            {
                i++;
            }
            node->next[i]=in3->next;
            node->next[i++]=node2->intercode->next;
            node->next[i++]=in3->next;
        }
        else{
            node->next[0]=in3->next;
            node->next[1]=node2->intercode->next;
            node->next[2]=in3->next;
        }
        sprintf(in2->content,"%s %s%s\n%s %s%d %s\n",go_to,label,"next",LABEL,label,labelnum2,":");
        node5->intercode=in2;
    }
    else if (match_with_var(node,5,WHILE,LP,EXP,RP,STMT))
    {
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="label";
        char LABEL[5]="LABEL";
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[1];
        TreeNode_ptr node3=node->children[2];
        TreeNode_ptr node4=node->children[3];
        TreeNode_ptr node5=node->children[4];
        //todo next
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->next=get_new_nextlinenumber();
        node->intercode=in3;
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=JUMP;
        in1->isprint=1;
        in1->content=malloc(50*sizeof(char));
        in1->next=in3->next;
        int labelnum1=alloc_label_number();
        int labelnum2=alloc_label_number();
        sprintf(in1->content,"%s %s %s %s%d\n%s %s%d\n%s %s%d %s\n",i_f,node3->intercode->content,go_to,label,labelnum1,go_to,label,in3->next,LABEL,label,labelnum1,":");
        node3->intercode=in1;
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=LABEL;
        in2->isprint=1;
        in2->content=malloc(50*sizeof(char));
        sprintf(in2->content,"%s %s%d %s\n",LABEL,label,labelnum2,":");
        node2->intercode=in2;
        Intercode_ptr in4=malloc(sizeof(Intercode));
        in4->kind=JUMP;
        in4->content=malloc(50*sizeof(char));
        sprintf(in4->content,"%s %s %s\n",go_to,label,labelnum2);
        in4->isprint=1;
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in4;
        add_children(node,new_node);

    }
}
/// @brief 这个产生式用于产生1多个变量定义
/// @param node 
/// @param intercodelist 
void translate_DefList(TreeNode_ptr node){

}
/// @brief 产生一个定义
/// @param node 
/// @param intercodelist 
void translate_Def(TreeNode_ptr node){
    // node->intercode=NULL;
}
/// @brief 产生多个变量
/// @param node 
/// @param intercodelist 
void translate_DecList(TreeNode_ptr node){

}
/// @brief 产生一个变量
/// @param node 
/// @param intercodelist 
void translate_Dec(TreeNode_ptr node){

}

/// @brief 各种计算式
/// @param node 
/// @param intercodelist 
void translate_Exp(TreeNode_ptr node){
    
    if (match_with_var(node,3,EXP,ASSIGNOP,EXP)==1)
    {
        //必须赋值给变量
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        if (node1->SemanticInfo->isID==0)
        {
            printf("\033[33m warning: there is only defination for type such as struct,function but not for varaible \033[0m \n");
            return;
        }
        char* node1_temp=node1->intercode->res;
        //来自int
        //node2最后产生的变量
        char* node2_temp=node2->intercode->res;
        // char node2_temp[2]="v0\0";
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=ASSIGN;
        in1->content=malloc(50*sizeof(char));
        in1->isprint=1;
        sprintf(in1->content,"%s %s %s\n",node1_temp,":=",node2_temp);
        //赋值了前面的不用
        node1->intercode->content=node2->intercode->content;
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in1;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,AND,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"&&",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"&&",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        
    }
    else if (match_with_var(node,3,EXP,OR,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"||",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,EQ,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"==",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        node->intercode->content=in3->content;
    }
    else if (match_with_var(node,3,EXP,NEQ,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"!=",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,LT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"<",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        node->intercode=malloc(sizeof(Intercode));
        node->intercode->content=in3->content;
    }
    else if (match_with_var(node,3,EXP,LE,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,"<=",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,GT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,">",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        node->intercode=malloc(sizeof(Intercode));
        node->intercode->content=in3->content;
    }
    else if (match_with_var(node,3,EXP,GE,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s %s %s",in1_temp,">=",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,PLUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        // in3->content=concat(5,new," := ",in1_temp,"+",in2_temp);
        sprintf(in3->content,"%s %s %s %s %s\n",new," := ",in1_temp,"+",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,EXP,MINUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        in3->isprint=1;
        in3->content=malloc(50*sizeof(char));
        sprintf(in3->content,"%s %s %s %s %s\n",new,":=",in1_temp,"-",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        node->intercode->content=in3->content;
        node->intercode->res=in3->res;
    }
    else if (match_with_var(node,3,EXP,STAR,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->isprint=1;
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(5,new," := ",in1_temp,"*",in2_temp);
        sprintf(in3->content,"%s %s %s %s %s\n",new,":=",in1_temp,"*",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
        node->intercode->content=in3->content;
        node->intercode->res=new;
    }
    else if (match_with_var(node,3,EXP,DIV,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->intercode;
        Intercode_ptr in2=node2->intercode;
        char* in1_temp=in1->res;
        char* in2_temp=in2->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->isprint=1;
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(5,new," := ",in1_temp,"/",in2_temp);
        sprintf(in3->content,"%s %s %s %s %s\n",new,":=",in1_temp,"/",in2_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,3,LP,EXP,RP)==1)
    {
        TreeNode_ptr node1=node->children[1];
        node->intercode->content=node1->intercode->content;
        node->intercode->res=node1->intercode->res;
    }
    else if (match_with_var(node,2,MINUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[1];
        Intercode_ptr in1=node1->intercode;

        char* in1_temp=in1->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->isprint=1;
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(4,new," := ","-",in1_temp);
        sprintf(in3->content,"%s %s %s %s %s\n",new,":=","#0","-",in1_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        node->intercode=malloc(sizeof(Intercode));
        node->intercode->content=in3->content;
        node->intercode->res=in3->res;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,2,NOT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in1=node1->intercode;
        char* in1_temp=in1->res;
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->isprint=1;
        in3->res=malloc(50*sizeof(char));
        in3->res=new;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(4,new," := ","!",in1_temp);
        sprintf(in3->content,"%s %s %s %s\n",new," := ","!",in1_temp);
        TreeNode_ptr new_node=create_node(0,0,0,0);
        new_node->intercode=in3;
        add_children(node,1,new_node);
    }
    else if (match_with_var(node,4,ID,LP,ARGS,RP)==1)
    {
        //使用带参数函数
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=CALL;
        in1->isprint=1;
        char* temp=new_temp();
        
        in1->content=malloc(50*sizeof(char));
        if (strcmp(node1->ID,"write")==0)
        {
            char* n_temp=node2->intercode->res;
            sprintf(in1->content,"%s %s\n","WRITE",n_temp);
        }
        else
        {
            sprintf(in1->content,"%s %s %s %s\n",temp,":=","CALL",node1->ID);
            in1->res=malloc(50*sizeof(char));
            in1->res=temp;
        }
        node->intercode->content=in1->content;
        node->intercode->res=in1->res;
        TreeNode_ptr node3=node->children[3];
        node3->intercode=in1;
    }
    else if (match_with_var(node,3,ID,LP,RP)==1)
    {
        //使用不带参数函数
        //需要判断是否为read/write函数
        TreeNode_ptr node1=node->children[0];
        if (strcmp(node1->ID,"read")==0)
        {
            Intercode_ptr in=malloc(sizeof(Intercode));
            in->kind=READ;
            char* temp=new_temp();
            in->content = malloc(50 * sizeof(char)); 
            // in->content=concat(2,"READ ",temp);
            sprintf(in->content,"%s %s\n","READ",temp);
            in->res=malloc(50*sizeof(char));
            in->res=temp;
            TreeNode_ptr node1=node->children[2];
            node1->intercode=in;
            in->isprint=1;
            node->intercode=malloc(sizeof(Intercode));
            node->intercode->content=in->content;
            node->intercode->res=in->res;
            //addIntercode(intercodelist,in);
        }
        else if (strcmp(node1->ID,"write")==0)
        {
            //事实上用不上这里
            Intercode_ptr in=malloc(sizeof(Intercode));
            in->kind=READ;
            in->content=malloc(50*sizeof(char));
            char* temp=new_temp();
            // in->content=concat(2,"WRITE ",temp);
            sprintf(in->content,"%s %s\n","WRITE",temp);
            // node->SemanticInfo->intercode=in;
            //addIntercode(intercodelist,in);
            in->isprint=1;
            node->children[2]->intercode=in;
            // in->isprint=1;
            node->intercode=malloc(sizeof(Intercode));
            node->intercode->content=in->content;
            node->intercode->res=in->res;
        }
        else
        {
            Intercode_ptr in=malloc(sizeof(Intercode));
            in->kind=FUNCTION;
            char* temp=new_temp();
            // in->content=concat(4,temp," := ","CALL ",node1->SemanticInfo->name);
            sprintf(in->content,"%s %s %s %s\n",temp," := ","CALL",node1->SemanticInfo->name);
            // node->SemanticInfo->intercode=in;
            //addIntercode(intercodelist,in);
            in->isprint=1;
            in->res=malloc(50*sizeof(char));
            in->res=temp;
            node->children[2]->intercode=in;
            node->intercode=malloc(sizeof(Intercode));
            node->intercode->content=in->content;
            node->intercode->res=in->res;
        }
    }
    else if (match_with_var(node,4,EXP,LB,EXP,RB)==1)
    {
        //数组不出现，暂不实现
        
    }
    else if (match_with_var(node,3,EXP,DOT,ID)==1)
    {
        //结构体，不出现，暂不实现
    }
    else if (match_with_var(node,1,ID)==1)
    {
       //不需要处理
       TreeNode_ptr node1=node->children[0];
       Intercode_ptr in1=malloc(sizeof(Intercode));
       in1->kind=ASSIGN;
       SemanticInfo_ptr s=hash_table_lookup(GLOBAL_HASH_TABLE,node1->ID);
       char* temp=NULL;
       if (s)
       {    
            if (s->temp)
            {
                //已经有临时变量了
                temp=s->temp;
            }
            else
            {
                //没有临时变量
                temp=new_temp();
                s->temp=temp;
            }
       }
       in1->content=malloc(50*sizeof(char));
    //    in1->isprint=1;
       sprintf(in1->content,"%s %s %s\n",temp,":=",node1->ID);
       in1->res=malloc(50*sizeof(char));
       printf("[EXP]%s\n",temp);
       in1->res=temp;
       node1->intercode=in1;
       node->intercode=malloc(sizeof(Intercode));
       node->intercode->content=in1->content;
       node->intercode->res=in1->res;
    }
    else if (match_with_var(node,1,INT)==1)
    {
        //我们使用#表示立即数
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in=malloc(sizeof(Intercode));
        // char int_val[10];  // enough for sign, 10 digits, and '\0'
        // printf("%d",node1->intval);
        // sprintf(int_val,"%d",node1->intval);
        // printf("%s",int_val);     
        char* temp=new_temp();
        in->kind=ASSIGN;
        in->isprint=1;
        in->res=malloc(50*sizeof(char));
        in->res=temp;
        in->content=malloc(50*sizeof(char));
        // in->content=concat(4,temp," := ","#",int_val);
        sprintf(in->content,"%s %s %s%d\n",temp,":=","#",node1->intval);
        printf("[translate_exp]:%s",in->content);
        node1->intercode=in;
        node->intercode=malloc(sizeof(Intercode));
        node->intercode->content=in->content;
        node->intercode->res=in->res;
    }
    else if (match_with_var(node,1,FLOAT)==1)
    {
        //我们使用#表示立即数
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in=malloc(sizeof(Intercode));
        // char float_val[10];
        // sprintf(float_val,"%f",node1->floatval);
        char* temp=new_temp();
        in->kind=ASSIGN;
        in->isprint=1;
        in->res=malloc(50*sizeof(char));
        in->res=temp;
        sprintf(in->content,"%s %s %s%f\n",temp," := ","#",node1->floatval);
        node1->intercode=in;
        //addIntercode(intercodelist,in);
        node->intercode=malloc(sizeof(Intercode));
        node1->intercode->content=in->content;
        node->intercode->res=in->res;
    }
    else{

    }
}
void translate_Args(TreeNode_ptr node){
    if (match_with_var(node,3,EXP,COMMA,ARGS)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[1];
        Intercode_ptr in1=malloc(sizeof(Intercode));
        char* temp=node1->intercode->res;
        in1->kind=PARAM;
        in1->isprint=1;
        in1->content=malloc(50*sizeof(char));
        // in1->content=concat(3,node2->SemanticInfo->intercode->content,temp," ");
        sprintf(in1->content,"%s %s\n","ARG",temp);
        node2->intercode=in1;
    }
    else if (match_with_var(node,1,EXP)==1)
    {
       TreeNode_ptr node1=node->children[0];
       Intercode_ptr in1=malloc(sizeof(Intercode));
       in1->kind=PARAM;
       char* temp=node1->intercode->res;
    //    char* temp=NULL;
       in1->isprint=1;
       in1->content=malloc(50*sizeof(char));
       sprintf(in1->content,"%s %s\n","ARG",temp);
    //    in1->content=strcat("PARAM",temp);
       TreeNode_ptr node2=create_node(0,0,0,0);
       node2->intercode=in1;
       node->intercode=malloc(sizeof(Intercode));
       node->intercode->content=in1->content;
       node->intercode->res=temp;
       add_children(node,1,node2);
    }
}
// 生成临时变量名（需手动释放内存）
char* new_temp() {
    static int counter = 0;      // 静态计数器
    char buffer[32];             // 临时缓冲区
    snprintf(buffer, sizeof(buffer), "v%d", counter++);
    return strdup(buffer);       // 返回动态复制的字符串
}

// 初始化动态数组
IntercodeList_ptr initIntercodeList(int initialCapacity) {
    // Allocate memory for the IntercodeList structure itself
    IntercodeList_ptr list = (IntercodeList_ptr)malloc(sizeof(IntercodeList));
    
    // Allocate memory for the array of Intercode_ptr with the given capacity
    list->codes = (Intercode_ptr*)malloc(sizeof(Intercode_ptr) * initialCapacity);
    
    // Initialize size and capacity
    list->size = 0;
    list->capacity = initialCapacity;
    
    // Return the pointer to the newly created IntercodeList
    return list;
}


// 释放内存
void freeIntercodeList(IntercodeList_ptr list) {
    for (int i = 0; i < list->size; i++) {
        free(list->codes[i]->content);  // 释放字符串内存
        free(list->codes[i]);           // 释放Intercode结构体内存
    }
    free(list->codes);                  // 释放数组内存
    list->size = 0;
    list->capacity = 0;
}
void DisplayIntercodelist(TreeNode_ptr node){
    if (node==NULL)
    {
        return;
    }
    if (node->intercode)
    {
        
        if (node->intercode->content&&node->intercode->isprint==1)
        {
            if (node->intercode->next>0)
            {
                // printf("--------------\n%d %d\n---------------\n",node->intercode->next,global_next[node->intercode->next]);
                //这里由于next的传递在前面已经完成了，所以哪怕已经传递成功，但木已成舟，只能在这里重新组装
                char* str=replace_next_with_int(node->intercode->content,global_next[node->intercode->next]);
                node->intercode->content=str;
            }
            
            printf("%s",node->intercode->content);
        }
    }
    for (int i = 0; i < node->child_count; i++)
    {
        // printf("%d %d\n",node->token,node->child_count);
        DisplayIntercodelist(node->children[i]);
    }
}
int alloc_label_number(){
    static int number=1;
    int raw=number;
    number++;
    return raw;
}
char* replace_next_with_int(const char* original, int num) {
    if (!original) return NULL;

    const char* next_pos = strstr(original, "next");
    if (!next_pos) {
        return strdup(original);
    }

    char num_str[20];
    int num_len = snprintf(num_str, sizeof(num_str), "%d", num);
    if (num_len < 0) {
        return NULL;
    }

    size_t orig_len = strlen(original);
    size_t prefix_len = next_pos - original;
    size_t suffix_len = orig_len - (prefix_len + 4);

    size_t total_len = prefix_len + num_len + suffix_len + 1;
    char* result = (char*)malloc(total_len);
    if (!result) return NULL;

    memcpy(result, original, prefix_len);
    memcpy(result + prefix_len, num_str, num_len);
    memcpy(result + prefix_len + num_len, next_pos + 4, suffix_len + 1);

    return result;
}

int get_new_nextlinenumber(){
    static int count=1;
    int raw=count;
    count++;
    return raw;
}
