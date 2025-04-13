/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-04-12 22:09:12
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-14 00:01:50
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
// #include <stdio.h>
#include <stdarg.h>
// #include <stdlib.h>
// #include <string.h>



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
//void addIntercode(IntercodeList_ptr list, Intercode_ptr code);
char* split_before_colon(const char* str);
char* new_temp();
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
    }
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
            node->SemanticInfo->intercode=dec_mem;
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
    if (intercode->content) {
        snprintf(intercode->content, len, "FUNCTION%s", func_name);
        printf("[translate_ExtDef]:def function intercode is %s\n", intercode->content);
        node->SemanticInfo->intercode=intercode;
        //addIntercode(intercodelist, intercode);
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
        TreeNode_ptr child=node->children[1];
        char param[5]="PARAM ";
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=PARAM;
        in->content=malloc(50*sizeof(char));
        in->content=strcat(param,child->SemanticInfo->name);
        node->SemanticInfo->intercode=in;
    }
    else{

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
    if (node1->SemanticInfo->intercode->isneednext==1)
    {
        if (node1->SemanticInfo->intercode->next)
        {
            sprintf(node1->SemanticInfo->intercode->next,"%d",node->linenum);
        }
        else{
            node1->SemanticInfo->intercode->next=malloc(50*sizeof(char));
            sprintf(node1->SemanticInfo->intercode->next,"%d",node->linenum);
        }
        
        
    }
}
/// @brief 各种表达式
/// @param node 
/// @param intercodelist 
void translate_Stmt(TreeNode_ptr node){
    if (match_with_var(node,2,EXP,SEMI)==1)
    {
        TreeNode_ptr child=node->children[0];
        node->SemanticInfo->intercode=malloc(sizeof(Intercode));
    }
    else if (match_with_var(node,1,COMP_STM)==1)
    {
        //定义在函数体中重新定义一个过程，由于假设，不用管这个,不存在嵌套过程
    }
    else if (match_with_var(node,3,RETURN,EXP,SEMI)==1)
    {
        TreeNode_ptr node2=node->children[1];
        char re[6]="RETURN";
        Intercode_ptr in=malloc(sizeof(Intercode));
        in->kind=SVT_RETURN;
        //exp如果是运算式呢，需要s找到计算运算式的中间变量
        ///如果exp只是一个id，那前面必然已经定义了，这里可以使用
        if (node2->SemanticInfo->isID==1)
        {
            //是变量，则寻找变量名，我们所有中间代码的变量名使用原有变量名，方便寻找
            printf("[translate_Stmt]:return var name is %s\n",node2->SemanticInfo->name);
            in->content=strcat("RETURN",node2->SemanticInfo->name);
            //addIntercode(intercodelist,in);
        }
        //todo这里需要exp内容来辨别到底是一个计算式子，还是单纯一个数字
        else if (node2->SemanticInfo->name==NULL)
        {
            if (node2->SemanticInfo->val_type==SVT_INT)
            {
                printf("[translate_Stmt]:return int %d\n",node2->intval);
                char int_val[20];
                sprintf(int_val,"%d",node2->intval);
                in->content=strcat("RETURN",int_val);
                //addIntercode(intercodelist,in);
            }
            else if (node2->SemanticInfo->val_type==SVT_FLOAT)
            {
                printf("[translate_Stmt]:return int %f\n",node2->floatval);
                char float_val[20];
                sprintf(float_val,"%f",node2->floatval);
                in->content=strcat("RETURN",float_val);
                //addIntercode(intercodelist,in);
            }
            else
            {
                in->content="RETURN\n";
            }
            
        }
        node->SemanticInfo->intercode=in;
    }
    else if (match_with_var(node,5,IF,LP,EXP,RP,STMT)==1)
    {
        //IF表达式,这里的exp大多是布尔表达式
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=JUMP;
        in1->content=malloc(50*sizeof(char));
        in1->content="IF";
        TreeNode_ptr child1=node->children[0];
        child1->SemanticInfo->intercode=in1;

        TreeNode_ptr child2=node->children[4];
        //将true和false统一放入RP中
        TreeNode_ptr child3=node->children[3];
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=JUMP;
        in3->content=malloc(50*sizeof(char));
        in3->isneednext=1;
        if (child2->SemanticInfo->intercode->isneednext==1)
        {
            in3->next=child2->SemanticInfo->intercode->next;
        }
        else{
            in3->next=malloc(50*sizeof(char));
        }
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=JUMP;
        in2->content=malloc(50*sizeof(char));
        sprintf(in2->content,"%s%s%d\n%s%s%s\n%s%d\n",go_to,label,child2->linenum,go_to,label,in3->next,label,child2->linenum);
        child3->SemanticInfo->intercode=in2;
        node->SemanticInfo->intercode=in3;
    }
    else if (node->child_count==7)
    {
        //IF LP Exp RP Stmt ELSE Stmt  
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=JUMP;
        in1->content=malloc(50*sizeof(char));
        in1->content="IF";
        TreeNode_ptr child0=node->children[0];
        child0->SemanticInfo->intercode=in1;
        printf("%s",child0->SemanticInfo->intercode->content);
        TreeNode_ptr child1=node->children[3];
        TreeNode_ptr child2=node->children[4];
        TreeNode_ptr child3=node->children[6];
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=JUMP;
        in2->content=malloc(50*sizeof(char));
        sprintf(in2->content,"%s%s%d\n%s%s%d\n%s%d\n",go_to,label,child2->linenum,go_to,label,child3->linenum,label,child2->linenum);
        child1->SemanticInfo->intercode=in2;
        Intercode_ptr in3 =malloc(sizeof(Intercode));
        in3->kind=JUMP;
        in3->isneednext=1;
        // in3->next=malloc(50*sizeof(char));
        //绑定地址
        if (child2->SemanticInfo->intercode->isneednext==1&&child3->SemanticInfo->intercode->isneednext==1)
        {
            //2者的next一致
            in3->next=child2->SemanticInfo->intercode->next;
            child3->SemanticInfo->intercode->next=child2->SemanticInfo->intercode->next;
        }
        else if (child2->SemanticInfo->intercode->isneednext==1&&child3->SemanticInfo->intercode->next==0)
        {
            in3->next=child2->SemanticInfo->intercode->next;
        }
        else if (child2->SemanticInfo->intercode->isneednext==0&&child3->SemanticInfo->intercode->next==1)
        {
            in3->next=child3->SemanticInfo->intercode->next;
        }
        else if (child2->SemanticInfo->intercode->isneednext==0&&child3->SemanticInfo->intercode->next==0)
        {
            in3->next=malloc(50*sizeof(char));
        }

        if (child2->SemanticInfo->intercode->content)
        {
            sprintf(child2->SemanticInfo->intercode->content,"%s\n%s%s%s\n",child2->SemanticInfo->intercode->content,go_to,label,in3->next);
        }else{
            child2->SemanticInfo->intercode->content=malloc(50*sizeof(char));
            sprintf(child2->SemanticInfo->intercode->content,"%s%s%s\n",go_to,label,in3->next);
        }
        if (child3->SemanticInfo->intercode->content)
        {
            sprintf(child3->SemanticInfo->intercode->content,"%s%d\n%s\n%s%s%s\n",label,child3->linenum,child3->SemanticInfo->intercode->content,go_to,label,in3->next);
        }else{
            child3->SemanticInfo->intercode->content=malloc(50*sizeof(char));
            sprintf(child3->SemanticInfo->intercode->content,"%s%d\n%s\n%s%s%s\n",label,child3->linenum,child3->SemanticInfo->intercode->content,go_to,label,in3->next);

        }
        //sprintf(child3->SemanticInfo->intercode->content,"%s%d\n%s\n%s%s%s\n",label,child3->linenum,child3->SemanticInfo->intercode->content,go_to,label,in3->next);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,5,WHILE,LP,EXP,RP,STMT))
    {
        char i_f[2]="IF";
        char go_to[4]="GOTO";
        char label[5]="LABEL";
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node4=node->children[2];
        TreeNode_ptr node2=node->children[3];
        TreeNode_ptr node3=node->children[4];
        Intercode_ptr in1=malloc(sizeof(Intercode));
        in1->kind=JUMP;
        in1->content=malloc(50*sizeof(char));
        in1->content=i_f;
        node1->SemanticInfo->intercode=in1;
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=JUMP;
        in2->content=malloc(50*sizeof(char));
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=JUMP;
        in3->isneednext=1;
        in3->next=malloc(50*sizeof(char));
        sprintf(in2->content,"%s%s%d\n%s%s%s\n",go_to,label,node3->linenum,go_to,label,in3->next);
        node2->SemanticInfo->intercode=in2;
        sprintf(node3->SemanticInfo->intercode->content,"%s%d\n%s\n%s%s%d\n",label,node3->linenum,node3->SemanticInfo->intercode->content,go_to,label,node4->linenum);
        sprintf(node4->SemanticInfo->intercode->content,"%s%d\n%s",label,node4->linenum,node4->SemanticInfo->intercode->content);
        node->SemanticInfo->intercode=in3;
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
        //赋值，可以现在打印出来

        //必须赋值给变量
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        if (node1->SemanticInfo->isID==0)
        {
            printf("\033[33m warning: there is only defination for type such as struct,function but not for varaible \033[0m \n");
            return;
        }
        char *name=node1->SemanticInfo->name;
        //来自int
        Intercode_ptr in1=node2->SemanticInfo->intercode;
        //node2最后产生的变量
        // char* node2_temp=split_before_colon(in1->content);
        char node2_temp[2]="v0\0";
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=ASSIGN;
        in2->content=malloc(50*sizeof(char));
        // in2->content=concat(3,node1->SemanticInfo->name," := ",node2_temp);
        sprintf(in2->content,"%s\t%s\t%s\n",node1->SemanticInfo->name," := ",node2_temp);
        //addIntercode(intercodelist,in2);
        node->SemanticInfo->intercode=in2;
    }
    else if (match_with_var(node,3,EXP,AND,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        //这里不加入list了，在if中会打印的
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"&&",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"&&",in2_temp);
        node->SemanticInfo->intercode=in3;
        
    }
    else if (match_with_var(node,3,EXP,OR,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"||",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"||",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,EQ,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"==",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"==",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,NEQ,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"!=",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"!=",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,LT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"<",in2_temp);
        in3->content=malloc(50*sizeof(char));
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"<",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,LE,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,"<=",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,"<=",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,GT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,">",in2_temp);
        in3->content=malloc(50*sizeof(char));
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,">",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,GE,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=RELOP;
        // in3->content=concat(3,in1_temp,">=",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\n",in1_temp,">=",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,PLUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        // in3->content=concat(5,new," := ",in1_temp,"+",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\t%s\n",new," := ",in1_temp,"+",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,MINUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        // in3->content=concat(5,new," := ",in1_temp,"-",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\t%s\n",new," := ",in1_temp,"-",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,STAR,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        // in3->content=concat(5,new," := ",in1_temp,"*",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\t%s\n",new," := ",in1_temp,"*",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,EXP,DIV,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        Intercode_ptr in2=node2->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* in2_temp=split_before_colon(in2->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        // in3->content=concat(5,new," := ",in1_temp,"/",in2_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\t%s\n",new," := ",in1_temp,"/",in2_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,3,LP,EXP,RP)==1)
    {
        //不会使用的
    }
    else if (match_with_var(node,2,MINUS,EXP)==1)
    {
        TreeNode_ptr node1=node->children[1];
        Intercode_ptr in1=node1->SemanticInfo->intercode;

        char* in1_temp=split_before_colon(in1->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        in3->content=malloc(50*sizeof(char));
        // in3->content=concat(4,new," := ","-",in1_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\n",new," := ","~",in1_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,2,NOT,EXP)==1)
    {
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in1=node1->SemanticInfo->intercode;
        char* in1_temp=split_before_colon(in1->content);
        char* new=new_temp();
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=CACULATE;
        // in3->content=concat(4,new," := ","!",in1_temp);
        sprintf(in3->content,"%s\t%s\t%s\t%s\n",new," := ","!",in1_temp);
        node->SemanticInfo->intercode=in3;
    }
    else if (match_with_var(node,4,ID,LP,ARGS,RP)==1)
    {
        //使用带参数函数
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=node2->SemanticInfo->intercode;
        Intercode_ptr in2=malloc(sizeof(Intercode));
        in2->kind=ARG;
        // in2->content=concat(2,"ARG",in1->content);
        in2->content=malloc(50*sizeof(char));
        sprintf(in2->content,"%s\t%s\n","ARG",in1->content);
        //addIntercode(intercodelist,in2);
        Intercode_ptr in3=malloc(sizeof(Intercode));
        in3->kind=FUNCTION;
        char* temp=new_temp();
        // in3->content=concat(4,temp," := ","CALL",node1->SemanticInfo->name);
        in3->content=malloc(50*sizeof(char));
        sprintf(in3->content,"%s\t%s\t%s\t%s\n",temp," := ","CALL",node1->SemanticInfo->name);
        //addIntercode(intercodelist,in3);
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
            sprintf(in->content,"%s\t%s\n","READ",temp);
            node->SemanticInfo->intercode=in;
            //addIntercode(intercodelist,in);
        }
        else if (strcmp(node1->ID,"write")==0)
        {
            Intercode_ptr in=malloc(sizeof(Intercode));
            in->kind=READ;
            char* temp=new_temp();
            // in->content=concat(2,"WRITE ",temp);
            sprintf(in->content,"%s\t%s\n","WRITE",temp);
            node->SemanticInfo->intercode=in;
            //addIntercode(intercodelist,in);
        }
        else
        {
            Intercode_ptr in=malloc(sizeof(Intercode));
            in->kind=FUNCTION;
            char* temp=new_temp();
            // in->content=concat(4,temp," := ","CALL ",node1->SemanticInfo->name);
            sprintf(in->content,"%s\t%s\t%s\t%s\n",temp," := ","CALL",node1->SemanticInfo->name);
            node->SemanticInfo->intercode=in;
            //addIntercode(intercodelist,in);
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
    }
    else if (match_with_var(node,1,INT)==1)
    {
        //我们使用#表示立即数
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in=malloc(sizeof(Intercode));
        char int_val[10];  // enough for sign, 10 digits, and '\0'
        printf("%d",node1->intval);
        sprintf(int_val,"%d",node1->intval);
        printf("%s",int_val);     
        char* temp=new_temp();
        in->kind=ASSIGN;
        in->content=malloc(50*sizeof(char));
        // in->content=concat(4,temp," := ","#",int_val);
        sprintf(in->content,"%s\t%s\t%s\t%s\n",temp," := ","#",int_val);
        printf("[translate_exp]:%s",in->content);
        node->SemanticInfo->intercode=in;
        //addIntercode(intercodelist,in);
    }
    else if (match_with_var(node,1,FLOAT)==1)
    {
        //我们使用#表示立即数
        TreeNode_ptr node1=node->children[0];
        Intercode_ptr in=malloc(sizeof(Intercode));
        char float_val[10];
        sprintf(float_val,"%f",node1->floatval);
        char* temp=new_temp();
        in->kind=ASSIGN;
        sprintf(in->content,"%s\t%s\t%s\t%s\n",temp," := ","#",float_val);
        node->SemanticInfo->intercode=in;
        //addIntercode(intercodelist,in);

    }
    else{

    }
}
void translate_Args(TreeNode_ptr node){
    if (match_with_var(node,3,EXP,COMMA,ARGS)==1)
    {
        TreeNode_ptr node1=node->children[0];
        TreeNode_ptr node2=node->children[2];
        Intercode_ptr in1=malloc(sizeof(Intercode));
        char* temp=split_before_colon(node1->SemanticInfo->intercode->content);
        in1->kind=ASSIGN;
        // in1->content=concat(3,node2->SemanticInfo->intercode->content,temp," ");
        sprintf(in1->content,"%s\t%s\t%s\n",node2->SemanticInfo->intercode->content,temp," ");
        node->SemanticInfo->intercode=in1;

    }
    else if (match_with_var(node,1,EXP)==1)
    {
       TreeNode_ptr node1=node->children[0];
       Intercode_ptr in1=malloc(sizeof(Intercode));
       in1->kind=ASSIGN;
       char* temp=split_before_colon(node1->SemanticInfo->intercode->content);
       in1->content=strcat(temp," ");
       node->SemanticInfo->intercode=in1;
    }
}

char* split_before_colon(const char* str) {
    if (str == NULL) return NULL;  // 检查输入合法性

    // 查找冒号的位置
    char* colon_pos = strchr(str, ' ');
    if (colon_pos == NULL) {
        return NULL;  // 没有冒号则返回 NULL
    }

    // 计算冒号前的子字符串长度
    size_t prefix_len = colon_pos - str;

    // 动态分配内存（+1 用于存放 '\0'）
    char* result = (char*)malloc(prefix_len + 1);
    if (result == NULL) {
        return NULL;  // 内存分配失败
    }

    // 复制子字符串
    strncpy(result, str, prefix_len);
    result[prefix_len] = '\0';  // 添加终止符

    return result;
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


// 添加中间代码到数组
//void addIntercode(IntercodeList_ptr list, Intercode_ptr code) {
//     if (list->size >= list->capacity) {
//         // 动态扩容（通常按2倍策略）
//         list->capacity *= 2;
//         list->codes = (Intercode_ptr*)realloc(list->codes, sizeof(Intercode_ptr) * list->capacity);
//     }
//     list->codes[list->size++] = code;
// }

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
    if (node->SemanticInfo)
    {
        
        if (node->SemanticInfo->intercode&&node->SemanticInfo->intercode->content)
        {
            // printf("%d\n",node->token);
            printf("%s",node->SemanticInfo->intercode->content);
        }
    }
    for (int i = 0; i < node->child_count; i++)
    {
        DisplayIntercodelist(node->children[i]);
    }
}
// void dfs(TreeNode *node) {
//     if (node == NULL) return;
    
//     // 1. 访问当前节点（这里打印数据）
//     printf("%d ", node->data);
    
//     // 2. 递归遍历所有子节点
//     TreeNode *child = node->firstChild;
//     while (child != NULL) {
//         dfs(child);          // 递归处理子节点
//         child = child->nextSibling; // 移动到下一个兄弟节点
//     }
// }
