/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 16:16:31
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-13 10:55:19
 * @FilePath: /Lab/src/SemanticInfo.c
 * @Description: file to definit semantic information
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include "../include/CmmparserTypes.h"
#include "../syntax.tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
int check_on_logic_caculate(HashTable_ptr hashtable,TreeNode_ptr father,TreeNode_ptr node1,TreeNode_ptr node2);
int match_with_var(TreeNode_ptr node,int child_num,...);
TypeEntry_ptr find_type_entry(SemanticmuldefInfo_ptr s, int target_type);
void SetHashTable_Program(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Specifier(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_ExtDefList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_FunDec(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Compstm(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_DefList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_VarDec(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Dec(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_DecList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Def(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Stmt(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_StmtList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_ExtDef(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_ExtDecList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Exp(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_ParamDec(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_VarList(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Args(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_StructSpecifier(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_Tag(HashTable_ptr hashtable,TreeNode_ptr node);
void SetHashTable_OptTag(HashTable_ptr hashtable,TreeNode_ptr node);

/// @brief 为每个节点创建一个语义属性
/// @param type_id 文法符号id，用于后续在hashtable中映射
/// @param issemanticValue 是否为终结符
/// @return semanticinfo 指针
SemanticInfo_ptr create_semanticinfo(int issemanticValue,int token){
    SemanticInfo_ptr s=malloc(sizeof(SemanticInfo));
    s->issemanticValue=issemanticValue;
    s->Type_id=token;
    s->name=NULL;
    s->isfunction=0;
    s->isstruct=0;
    s->isArray=0;
    s->val_type=SVT_VOID;
    s->semanticarrayinfo=NULL;
    s->semanticFunctioninfo=NULL;
    s->semanticmuldefinfo=NULL;
    s->isdefined=0;
    s->isID=0;
    s->ismulidef=0;
    s->intercode=NULL;
    // s->semanticiddefinfo=NULL;
}

void SetHashTable(HashTable_ptr hashtable,TreeNode_ptr node){
    switch (node->token)
    {
    case PROGRAM:
        SetHashTable_Program(hashtable,node);
        break;
    case EXT_DEF_LIST:
        SetHashTable_ExtDefList(hashtable,node);
        break;
    case EXT_DEF:
        SetHashTable_ExtDef(hashtable,node);
        break;
    case EXT_DEC_LIST:
        SetHashTable_ExtDecList(hashtable,node);
        break;
    case SPECIFIER:
        SetHashTable_Specifier(hashtable,node);
        break;
    case STRUCT_SPECIFIER:
        SetHashTable_StructSpecifier( hashtable, node);
        break;
    case OPT_TAG:
        SetHashTable_OptTag(hashtable,node);
        break;
    case TAG:
        SetHashTable_Tag(hashtable,node);
        break;
    case VAR_DEC:
        SetHashTable_VarDec(hashtable,node);
        break;
    case FUN_DEC:
        SetHashTable_FunDec(hashtable,node);
        break;
    case VAR_LIST:
        SetHashTable_VarList(hashtable,node);
        break;
    case PARAM_DEC:
        SetHashTable_ParamDec(hashtable,node);
        break;
    case COMP_STM:
        SetHashTable_Compstm(hashtable,node);
        break;
    case STMT_LIST:
        SetHashTable_StmtList(hashtable,node);
        break;
    case STMT:
        SetHashTable_Stmt(hashtable,node);
        break;
    case DEF_LIST:
        SetHashTable_DefList(hashtable,node);
        break;
    case DEF:
        SetHashTable_Def(hashtable,node);
        break;
    case DEC_LIST:
        SetHashTable_DecList(hashtable,node);
        break;
    case DEC:
        SetHashTable_Dec(hashtable,node);
        break;
    case EXP:
        SetHashTable_Exp(hashtable,node);
        break;
    case ARGS:
        SetHashTable_Args( hashtable, node);
        break;
    default:
        break;
    }
    return;
}      

void SetHashTable_Program(HashTable_ptr hashtable,TreeNode_ptr node){

}

void SetHashTable_Specifier(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count!=1)
    {
        return;
    }
    TreeNode_ptr child=node->children[0];
    if (child->token==TYPE)
    {
        // node->SemanticInfo->val_type=(child->token==INT)?SVT_FLOAT:SVT_INT;
        // printf("[SPECIFIRE]:%s",child->ID);
        if (strcmp(child->ID,"int")==0)
        {
            node->SemanticInfo->val_type=SVT_INT;
        }
        else if (strcmp(child->ID,"float")==0)
        {
            node->SemanticInfo->val_type=SVT_FLOAT;
        }
        
    }
    else if (node->children[0]->token==STRUCT_SPECIFIER)
    {
        node->SemanticInfo=child->SemanticInfo;
    }
}
void SetHashTable_StructSpecifier(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==5)
    {
        if (match_with_var(node,5,STRUCT,OPT_TAG,LC,DEF_LIST,RC)==1)
        {
            //结构体定义
            TreeNode_ptr child1=node->children[1];
            TreeNode_ptr child2=node->children[3];
            node->SemanticInfo=child2->SemanticInfo;
            node->SemanticInfo->isstruct=1;
            node->SemanticInfo->name=child1->SemanticInfo->name;
            node->SemanticInfo->val_type=SVT_STRUCT;
            SemanticInfo_ptr p=hash_table_lookup(hashtable,child1->SemanticInfo->name);
            if (!p)
            {
                hash_table_insert(hashtable,node->SemanticInfo);
            }
            else
            {
                reporterror(node->linenum,ConflictStructDefinition,"Redinifition of the struct");
            }
        }
        
    }
    else if (node->child_count==2)
    {
        if (match_with_var(node,2,STRUCT,TAG)==1)
        {
            //结构体里啥都没有，这种一般是使用结构体，或者利用struct tag 去定义一个结构体
            // SemanticInfo_ptr p=malloc(sizeof(SemanticInfo));
            // TreeNode_ptr node=node->children[1];
            // p=node->SemanticInfo;
            // p->isstruct=1;
            // p->semanticarrayinfo=NULL;
            // hash_table_insert(hashtable,p);
            // node->SemanticInfo=p;
            TreeNode_ptr child=node->children[1];
            SemanticInfo_ptr p=hash_table_lookup(hashtable,child->SemanticInfo->name);
            if (!p)
            {
                //没有查到结构体
                reporterror(node->linenum,UndefinedStruct,"can not use undefined struct");
            }
            else if (p)
            {
                //是否是结构体名
                if (p->isstruct==0)
                {
                    //使用了非结构体的变量名
                    reporterror(node->linenum,MemberAccessOnNonStruct,"can not use that variable as struct");
                }
                else
                {
                    node->SemanticInfo=p;
                    node->SemanticInfo->isstruct=1;
                } 
            }
        }
    }
    
    

}

//使用struct的时候定义的id
void SetHashTable_Tag(HashTable_ptr hashtable,TreeNode_ptr node){
    SemanticInfo_ptr p=malloc(sizeof(SemanticInfo));
    p->isID=1;
    TreeNode_ptr child=node->children[0];
    p->name=child->ID;
    node->SemanticInfo=p;
}
void SetHashTable_OptTag(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        SemanticInfo_ptr p=malloc(sizeof(SemanticInfo));
        p->isID=1;
        TreeNode_ptr child=node->children[0];
        p->name=child->ID;
        node->SemanticInfo=p;
    }
    else if (node->child_count==0)
    {
        return;
    } 
    
}



void SetHashTable_FunDec(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==4)
    {
        // TreeNode_ptr child1=node->children[0];
        // TreeNode_ptr child2=node->children[1];
        // TreeNode_ptr child3=node->children[2];
        // TreeNode_ptr child4=node->children[3];
        // node->SemanticInfo->isfunction=1;
        // node->SemanticInfo->name=child1->ID;
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child3=node->children[2];
        SemanticFunctionInfo_ptr p=malloc(sizeof(SemanticFunctionInfo));
        node->SemanticInfo->isfunction=1;
        node->SemanticInfo->name=child1->ID;
        printf("[fundec]:%s",child1->ID);
        node->SemanticInfo->semanticFunctioninfo=child3->SemanticInfo->semanticFunctioninfo;
        // printf("%d,%s",node->SemanticInfo->ismulidef,node->SemanticInfo->name);
        if (hash_table_lookup(hashtable,node->SemanticInfo->name))
        {
            reporterror(node->linenum,FunctionRedefinition,"Redinition the function");
            hash_table_insert(hashtable,node->SemanticInfo);
            push(Function_Stack,node->SemanticInfo->name);
            printf("[fundec]push %s\n",node->SemanticInfo->name);
        }
        else
        {
            hash_table_insert(hashtable,node->SemanticInfo);
            push(Function_Stack,node->SemanticInfo->name);
            printf("[fundec]push %s\n",node->SemanticInfo->name);
        }
        return;
    }
    else if (node->child_count==3)
    {
        if (match_with_var(node,3,ID,LP,RP)==1)
        {
            TreeNode_ptr child1=node->children[0];
            TreeNode_ptr child2=node->children[1];
            TreeNode_ptr child3=node->children[2];
            node->SemanticInfo->isfunction=1;
            node->SemanticInfo->name=child1->ID;
            node->SemanticInfo->semanticFunctioninfo=NULL;
            if (hash_table_lookup(hashtable,node->SemanticInfo->name))
            {
                reporterror(node->linenum,FunctionRedefinition,"Redinition the function");
                hash_table_insert(hashtable,node->SemanticInfo);
                push(Function_Stack,node->SemanticInfo->name);
                printf("[fundec]push %s\n",node->SemanticInfo->name);
            }
            else
            {
                hash_table_insert(hashtable,node->SemanticInfo);
                push(Function_Stack,node->SemanticInfo->name);
                printf("[fundec]push %s\n",node->SemanticInfo->name);
            }
        }
        else if (match_with_var(node,3,ID,LP,VAR_LIST)==1)
        {
            return;
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
/// @brief 需要说明这里这个也是必然在Fundec中，所以这里直接开启了Func了
/// @param hashtable 
/// @param node 
void SetHashTable_VarList(HashTable_ptr hashtable,TreeNode_ptr node){
    node->SemanticInfo->isfunction=1;
    SemanticFunctionInfo_ptr p=malloc(sizeof(SemanticFunctionInfo));
    if (node->child_count==3)
    {
        //todo 动态内存分配
        TreeNode_ptr child3=node->children[2];
        TreeNode_ptr child1=node->children[0];
        p->val_number=p->val_number+1;
        p=child3->SemanticInfo->semanticFunctioninfo;
        p->val_type=realloc(p->val_type,p->val_number*sizeof(int));
        p->val_name=realloc(p->val_name,p->val_number*sizeof(char*));
        p->val_type[p->val_number-1]=child1->SemanticInfo->val_type;
        p->val_name[p->val_number-1]=child1->SemanticInfo->name;

    }
    else if(match_with_var(node,1,PARAM_DEC)==1)
    {
        TreeNode_ptr child1=node->children[0];
        p->val_number=1; 
        p->val_name=malloc(p->val_number*sizeof(char*));
        p->val_name[p->val_number-1]=child1->SemanticInfo->name;
        p->val_type=malloc(p->val_number*sizeof(int));
        p->val_type[p->val_number-1]=child1->SemanticInfo->val_type;
        node->SemanticInfo->semanticFunctioninfo=p;
    }
}

/// @brief 这个函数向上传递函数参数只可能作为FunDec的参数
/// @param hashtable 
/// @param node 
void SetHashTable_ParamDec(HashTable_ptr hashtable,TreeNode_ptr node){
    if (match_with_var(node,2,SPECIFIER,VAR_DEC)==1)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        node->SemanticInfo=child2->SemanticInfo;
        //需要判断是否为数组，唯一考虑了可能上来数组定义
        if (child2->SemanticInfo->isArray==0)
        {
            node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            printf("%s",node->SemanticInfo->name);
        }
        else{
            node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            node->SemanticInfo->semanticarrayinfo->val_type=child1->SemanticInfo->val_type;
        }
        hash_table_insert(hashtable,node->SemanticInfo);
    }
    else if (match_with_var(node,1,VAR_DEC)==1)
    {
        TreeNode_ptr child=node->children[0];
        node->SemanticInfo=child->SemanticInfo;
        printf("%s",node->SemanticInfo->name);
        hash_table_insert(hashtable,node->SemanticInfo);
    }
}



void SetHashTable_Compstm(HashTable_ptr hashtable,TreeNode_ptr node){
    if (match_with_var(node,4,LC,DEF_LIST,STMT_LIST,RC)==1)
    {
        //这里应该不用做什么，因为规约进行，调用这个函数的时机应该是规约的时候调用，此时DEF_LIST,STMT_LIST应该已经定义好了
        //这里也检查不出什么错误   
        //错误全部在下面检查
    }
    else{
        return;
    }
}

void SetHashTable_DefList(HashTable_ptr hashtable,TreeNode_ptr node){
    //从def拿上来的可以是ismutidef内容，也可能只是一个id定义
    if (node->child_count==2)
    {
        //这里的任务仅仅是融合，在前面已经把变量insert过了，现在不需要insert
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        if (child1->SemanticInfo->ismulidef==0)
        {
            //即deflist产生空产生式
            if (child2->child_count==0)
            {
                SemanticInfo_ptr p=malloc(sizeof(SemanticInfo));
                p->val_type=SVT_VOID;
                p->ismulidef=1;
                SemanticmuldefInfo_ptr s=malloc(sizeof(SemanticFunctionInfo));
                s->type_count=1;
                TypeEntry_ptr* entries=malloc(s->type_count*sizeof(TypeEntry_ptr));
                // 分配 entries 指针数组
                s->entries = malloc(s->type_count * sizeof(TypeEntry*)); 

                // 处理第一个 TypeEntry (index 0)
                s->entries[0] = malloc(sizeof(TypeEntry)); // 分配 TypeEntry 结构体
                s->entries[0]->type = child1->SemanticInfo->val_type;
                s->entries[0]->var_count = 1; 

                // 分配 var_names 数组
                s->entries[0]->var_names = malloc(s->entries[0]->var_count * sizeof(char*));

                // 复制变量名（深拷贝）
                s->entries[0]->var_names[0] = child1->SemanticInfo->name;
                p->semanticmuldefinfo=s;
                node->SemanticInfo=p;
            }
            //多组定义式
            else if (child2->child_count==2)
            {
                //判断是否拥有child1的类型，如果有直接添加，反之则需要新增加一个entry
                node->SemanticInfo=child2->SemanticInfo;
                TypeEntry_ptr entry=find_type_entry(node->SemanticInfo->semanticmuldefinfo,child1->SemanticInfo->val_type);
                if (!entry)
                {
                    SemanticmuldefInfo_ptr s=node->SemanticInfo->semanticmuldefinfo;
                    //空，需要创建新的entry
                    int new_type_count = s->type_count + 1;
                    TypeEntry** new_entries = realloc(s->entries, 
                                                    new_type_count * sizeof(TypeEntry*));
                    if (!new_entries) {
                        // 处理内存分配失败
                        perror("realloc failed");
                        exit(EXIT_FAILURE);
                    }
                    s->entries = new_entries;

                    // 创建新条目
                    TypeEntry* new_entry = malloc(sizeof(TypeEntry));
                    new_entry->type = child1->SemanticInfo->val_type;
                    new_entry->var_count =1;

                    // 分配变量名数组
                    new_entry->var_names = malloc(new_entry->var_count * sizeof(char*));
                    for (int i = 0; i < new_entry->var_count; i++) {
                        new_entry->var_names[i] = 
                            strdup(child1->SemanticInfo->name); // 深拷贝
                    }
                    // 将新条目加入数组
                    s->entries[s->type_count] = new_entry;
                    s->type_count = new_type_count;
                }
                else
                {
                    //拥有这个类型
                    int new_var_count = entry->var_count + 1;

                    // 扩展 var_names 数组
                    char** new_names = realloc(entry->var_names, 
                                             new_var_count * sizeof(char*));
                    if (!new_names) {
                        // 处理内存分配失败
                        perror("realloc failed");
                        exit(EXIT_FAILURE);
                    }
                    entry->var_names = new_names;
            
                    // 添加新变量名（假设 semanticmuldefinfo 存储变量名数组）
                    // for (int i = 0; i < child_info->semanticmuldefinfo->count; i++) {
                    //     int dst_index = target_entry->var_count + i;
                    //     target_entry->var_names[dst_index] = 
                    //         strdup(child_info->semanticmuldefinfo->names[i]); // 深拷贝
                    // }
                    entry->var_names[new_var_count-1]=child1->SemanticInfo->name;
                    // 更新计数器
                    entry->var_count = new_var_count;
                }
            }
        }
        else if (child1->SemanticInfo->ismulidef==1)
        {
            //意味着def本身也是一个单类型多定义的方式，也是查看
            if (child2->child_count==0)
            {
                node->SemanticInfo=child1->SemanticInfo;
            }
            else if (child2->child_count==2)
            {
                node->SemanticInfo=child2->SemanticInfo;
                //child1必然只有一个类型，已经定义在val_type中
                TypeEntry_ptr entry=find_type_entry(node->SemanticInfo->semanticmuldefinfo,child1->SemanticInfo->val_type);
                if (!entry)
                {
                    SemanticmuldefInfo_ptr s=node->SemanticInfo->semanticmuldefinfo;
                    //空，需要创建新的entry
                    int new_type_count = s->type_count + 1;
                    TypeEntry** new_entries = realloc(s->entries, 
                                                    new_type_count * sizeof(TypeEntry*));
                    if (!new_entries) {
                        // 处理内存分配失败
                        perror("realloc failed");
                        exit(EXIT_FAILURE);
                    }
                    s->entries = new_entries;

                    // 创建新条目
                    TypeEntry* new_entry = malloc(sizeof(TypeEntry));
                    new_entry->type = child1->SemanticInfo->val_type;
                    new_entry->var_count =child1->SemanticInfo->semanticmuldefinfo->entries[0]->var_count;
                    // 分配变量名数组
                    new_entry->var_names = malloc(new_entry->var_count * sizeof(char*));
                    for (int i = 0; i < new_entry->var_count; i++) {
                        new_entry->var_names[i] = 
                            strdup(child1->SemanticInfo->semanticmuldefinfo->entries[0]->var_names[i]); // 深拷贝
                    }
                    // 将新条目加入数组
                    s->entries[s->type_count] = new_entry;
                    s->type_count = new_type_count;
                }
                else
                {
                    //拥有这个类型
                    int new_var_count = entry->var_count + child1->SemanticInfo->semanticmuldefinfo->entries[0]->var_count;

                    // 扩展 var_names 数组
                    char** new_names = realloc(entry->var_names, 
                                             new_var_count * sizeof(char*));
                    if (!new_names) {
                        // 处理内存分配失败
                        perror("realloc failed");
                        exit(EXIT_FAILURE);
                    }
                    entry->var_names = new_names;
            
                    // 添加新变量名（假设 semanticmuldefinfo 存储变量名数组）
                    for (int i = 0; i < child1->SemanticInfo->semanticmuldefinfo->entries[0]->var_count; i++) {
                        int dst_index = entry->var_count + i;
                        entry->var_names[dst_index] = 
                            strdup(child1->SemanticInfo->semanticmuldefinfo->entries[0]->var_names[i]); // 深拷贝
                    }
                    // entry->var_names[new_var_count-1]=child1->SemanticInfo->name;
                    // 更新计数器
                    entry->var_count = new_var_count;
                }
            }
        }
    }
}
void SetHashTable_VarDec(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        TreeNode_ptr child=node->children[0];
        node->SemanticInfo->isID=1;
        node->SemanticInfo->name=child->ID;
        // printf("%s",node->SemanticInfo->name);
    }
    else if (node->child_count==4)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[2];
        node->SemanticInfo=child1->SemanticInfo;
        node->SemanticInfo->isArray=1;
        SemanticArrayInfo_ptr p=malloc(sizeof(SemanticArrayInfo));
        p->val_type=SVT_VOID;//其中的元素类型尚且未知
        p->column_number=child2->intval;
        p->row_number=1;
        node->SemanticInfo->semanticarrayinfo=p;
        // hash_table_insert(hashtable,node->SemanticInfo);
    }
}

void SetHashTable_Dec(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        TreeNode_ptr child=node->children[0];
        node->SemanticInfo=child->SemanticInfo;
    }
    else if (node->child_count==3)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[2];
        //由于是def产生式，所以这里似乎可以暂时不判断类型，将类型判断留给Def来判断
        if (match_with_var(node,3,VAR_DEC,ASSIGNOP,EXP))
        {
            node->SemanticInfo=child1->SemanticInfo;
            //这里类型必然可以判断，如果exp是int,float自然，如果是id,则必然前面已经定义，否则进入报错，类型依然改为svt_void
            node->SemanticInfo->val_type=child2->SemanticInfo->val_type;            
            // //是一个尚未定义的数组
            // node->SemanticInfo=child1->SemanticInfo;
            // node->SemanticInfo->val_type=child2->SemanticInfo->val_type;
        }
        else{
            printf("[SetHashTable_Dec]:should not enter this function");
        }
    }    
}

///1这里定义的必然是一个类型的
void SetHashTable_DecList(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        //这里本意增加idlist就是为了处理多个变量定义的情况，既然只有一个，那就正常处理即可
        //正常insert
        TreeNode_ptr child=node->children[0];
        node->SemanticInfo->ismulidef=0;
        node->SemanticInfo=child->SemanticInfo;
    }
    else if (node->child_count==3)
    {
        //事实上这里有点偷懒，应当还需要记录类型，鉴于没有这类测试就索性算了。
        //意味着需要获得多个定义
        TreeNode_ptr child1=node->children[0];
        // TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child3=node->children[2];
        node->SemanticInfo->ismulidef=1;
        // if (!child3->SemanticInfo->semanticiddefinfo)
        // {
        //     p->number=2;
        //     p->val_name=malloc(p->number*sizeof(char*));
        //     p->val_name[0]=child1->SemanticInfo->name;
        //     p->val_name[1]=child3->SemanticInfo->name;
        // }
        // else
        // {
        //     p=child3->SemanticInfo->semanticiddefinfo;
        //     p->number=p->number+1;
        //     p->val_name=realloc(p->val_name,p->number*sizeof(char*));
        //     p->val_name[p->number-1]=child1->SemanticInfo->name;   
        // }
        if (!child3->SemanticInfo->semanticmuldefinfo)
        {
            SemanticmuldefInfo_ptr p=malloc(sizeof(SemanticmuldefInfo));
            //如果子节点是空的，说明存在多个定义
            p->type_count=1;
            //后续如果有多个定义需要扩容
            TypeEntry_ptr* type=malloc(p->type_count*sizeof(TypeEntry_ptr));
            p->entries=type;
            type[0] = malloc(sizeof(TypeEntry));
            type[0]->type=SVT_VOID;
            type[0]->var_count=2;
            char** var_names=malloc(type[0]->var_count*sizeof(char*));
            type[0]->var_names=var_names;
            var_names[0]=child1->SemanticInfo->name;
            var_names[1]=child3->SemanticInfo->name;
            node->SemanticInfo->semanticmuldefinfo=p;
        }
        else
        {
            //说明declist非空，说明要定义的不只2个
            //此时必然只有一个entries,只有到了deflist才会有多个entries
            SemanticmuldefInfo_ptr p=child3->SemanticInfo->semanticmuldefinfo;
            p->entries[0]->var_count+=1;
            p->entries[0]->var_names=realloc(p->entries[0]->var_names,p->entries[0]->var_count*sizeof(char*));
            p->entries[0]->var_names[p->entries[0]->var_count-1]=child1->SemanticInfo->name;
            node->SemanticInfo->semanticmuldefinfo=p;
        }
    }

}
//确保一次定义完全一整个int a,b,c的内容
void SetHashTable_Def(HashTable_ptr hashtable,TreeNode_ptr node){
    TreeNode_ptr child1=node->children[0];
    TreeNode_ptr child2=node->children[1];
    if (child2->SemanticInfo->ismulidef==0)
    {
        //只有一个变量
        if ((child1->SemanticInfo->val_type==child2->SemanticInfo->val_type)&&(child2->SemanticInfo->val_type!=SVT_VOID))
        {
            ///如果从下面定义上来拥有类型，说明下面已经把类型给定义了
            ///需要查看是否重复
            SemanticInfo_ptr p=hash_table_lookup(hashtable,child2->SemanticInfo->name);
            if (!p)
            {
                node->SemanticInfo=child2->SemanticInfo;
                hash_table_insert(hashtable,node->SemanticInfo);
            }
            else
            {
                reporterror(node->linenum,VariableNameRedefinition,"can not redefinition the variable");
                printf("1");
            }
        }
        //如果没有类型
        else if ((child1->SemanticInfo->val_type!=child2->SemanticInfo->val_type)&&(child2->SemanticInfo->val_type==SVT_VOID)&&(child1->SemanticInfo->val_type!=SVT_VOID))
        {
            SemanticInfo_ptr p=hash_table_lookup(hashtable,child2->SemanticInfo->name);
            if (!p)
            {
                node->SemanticInfo=child1->SemanticInfo;
                node->SemanticInfo->isID=1;
                node->SemanticInfo->name=child2->SemanticInfo->name;
                if (child2->SemanticInfo->isArray==1)
                {
                    node->SemanticInfo->isArray=1;
                    node->SemanticInfo->semanticarrayinfo=child2->SemanticInfo->semanticarrayinfo;
                }
                printf("[Def]%d\n",node->SemanticInfo->val_type);
                printf("[Def]:%s\n",node->SemanticInfo->name);
                hash_table_insert(hashtable,node->SemanticInfo);
            }
            else if(p)
            {
                reporterror(node->linenum,VariableNameRedefinition,"can not redefinition the variable");
                printf("2");
            }
            // else if (p&&p->isstruct==1)
            // {
            //     //利用结构体定义一个变量
            //     node->SemanticInfo=p;
            //     node->SemanticInfo->name=child2->SemanticInfo->name;
            // }
            
        } 
        else if ((child1->SemanticInfo->val_type!=child2->SemanticInfo->val_type)&&(child1->SemanticInfo->val_type!=SVT_VOID)&&(child2->SemanticInfo->val_type!=SVT_VOID))
        {
            reporterror(node->linenum,AssignmentTypeMismatch,"type with defination is miss type");
        }   
    }
    else if (child2->SemanticInfo->ismulidef==1)
    {
        //说明定义了多个变量，此时变量不在name
        node->SemanticInfo=child2->SemanticInfo;
        node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
        SemanticmuldefInfo_ptr p=node->SemanticInfo->semanticmuldefinfo;
        //现在这里必然还是只有一个type entry
        TypeEntry_ptr type=p->entries[0];
        int val_number=type->var_count;
        type->type=node->SemanticInfo->val_type;
        for (int i = 0; i < val_number; i++)
        {
            SemanticInfo_ptr s=hash_table_lookup(hashtable,type->var_names[i]);
            if (!s)
            {
                // reporterror(node->linenum,VariableNameRedefinition,"can not redefinition the variable");
                //如果没有就插入
                SemanticInfo_ptr new_val=malloc(sizeof(SemanticInfo));
                new_val->isID=1;
                new_val->name=type->var_names[i];
                new_val->val_type=type->type;
                hash_table_insert(hashtable,new_val);
            }
            else
            {
                reporterror(node->linenum,VariableNameRedefinition,"can not redefinition the variable");
            }
        }
    }
}


///stmt主要定义的是一些基本的语段结构，主要指除了定义语句外的其他语句，由于似乎没有涉及到错误类型可能发生，也没有改变什么语义属性
//基本路线是继续向上传递语义，这里暂时不处理，因为类型判断用不上
void SetHashTable_Stmt(HashTable_ptr hashtable,TreeNode_ptr node){
    if (match_with_var(node,3,RETURN,EXP,SEMI))
    {
        //由于不用考虑作用域，所以能走到这一步必然只有一个函数，我说的哈哈
        //todo 拿到functon在hashtable中的SemanticInfo,怎么拿过来呢
        char* name=pop(Function_Stack);
        printf("[stmt]:%s\n",name);
        SemanticInfo_ptr p=hash_table_lookup(hashtable,name);
        TreeNode_ptr child=node->children[1];
        if (p->isfunction==1&&p)
        {
            printf("[stmt]:%d,%d\n",p->val_type,child->SemanticInfo->val_type);
            //这里由于是自底向上，所以return必然会先规约，这里先记下，在ext那里比较
            p->val_type=child->SemanticInfo->val_type;
            // if (p->val_type!=child->SemanticInfo->val_type)
            // {
            //     reporterror(node->linenum,ReturnTypeMismatch,"miss type match for return");
            // }
        }
        else
        {
            printf("must be a function");
        }
    }
    
}
void SetHashTable_StmtList(HashTable_ptr hashtable,TreeNode_ptr node){
    
}


void SetHashTable_ExtDef(HashTable_ptr hashtable,TreeNode_ptr node){
    if (match_with_var(node,3,SPECIFIER,EXT_DEC_LIST,SEMI)==1)
    {
        return;
    }
    else if (match_with_var(node,2,SPECIFIER,SEMI)==1)
    {
        TreeNode_ptr child1=node->children[0];
        node->SemanticInfo=child1->SemanticInfo;
        printf("\033[33m warning: there is only defination for type such as struct,function but not for varaible \033[0m \n");
    }
    else if (match_with_var(node,3,SPECIFIER,FUN_DEC,COMP_STM)==1)
    {
        TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child1=node->children[0];
        node->SemanticInfo=child2->SemanticInfo;

        // node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
        printf("[ExtDef]:%s,%d\n",node->SemanticInfo->name,node->SemanticInfo->val_type);
        SemanticInfo_ptr a=hash_table_lookup(hashtable,child2->SemanticInfo->name);
        // if (a!=NULL)
        // {
        //     reporterror(node->linenum,FunctionRedefinition,"Redinition the function");
        // }
        // else{
        //     hash_table_insert(hashtable,node->SemanticInfo);
        // }
        if (a->val_type!=child1->SemanticInfo->val_type)
        {
            reporterror(node->linenum,ReturnTypeMismatch,"miss type match for return");
        }
        else
        {
            a->val_type=child1->SemanticInfo->val_type;
        }
        
        
    }
    // else if (match_with_var(node,3,SPECIFIER,FUN_DEC,SEMI))
    // {
        
    // }
}
void SetHashTable_ExtDecList(HashTable_ptr hashtable,TreeNode_ptr node){

}
void SetHashTable_ExtDefList(HashTable_ptr hashtable,TreeNode_ptr node){
    if (match_with_var(node,2,EXT_DEF,EXT_DEC_LIST)==1)
    {
        return;
    }
}



void SetHashTable_Exp(HashTable_ptr hashtable,TreeNode_ptr node){
    if (node->child_count==1)
    {
        TreeNode_ptr child=node->children[0];
        
        if (child->token==INT)
        {
            node=child;
            node->SemanticInfo->val_type=SVT_INT;
            // node=child;
        }
        else if (child->token==FLOAT)
        {
            node=child;
            node->SemanticInfo->val_type=SVT_FLOAT;
        }
        else
        {
            //使用之前必然已经定义，否则报错
            node->SemanticInfo->isID=1;
            printf("12314");
            printf("%s",child->ID);
            if (hash_table_lookup(hashtable,child->ID)==NULL)
            {
                reporterror(node->linenum,UndefinedVariable,"can not use undefined variable");
            }
            else
            {
                node->SemanticInfo=hash_table_lookup(hashtable,child->ID);
            }
        }
    }
    else if (node->child_count==2)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        if (match_with_var(node,2,MINUS,EXP)==1)
        {
            node->SemanticInfo=child2->SemanticInfo;
        }
        else if (match_with_var(node,2,NOT,EXP)==1)
        {
            node->SemanticInfo=child2->SemanticInfo;   
        }
    }
    
    else if (node->child_count==3)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child3=node->children[2];
        if (match_with_var(node,3,EXP,ASSIGNOP,EXP)==1)
        {
            ///赋值语句基本只能给变量赋值，所以地一个node必然是从id规约过来的
            if (child1->SemanticInfo->isID==1)
            {
                if ((child1->SemanticInfo->val_type!=child3->SemanticInfo->val_type)&&(child1->SemanticInfo->val_type!=SVT_VOID)&&(child3->SemanticInfo->val_type!=SVT_VOID))
                {
                    // printf("%d",child1->SemanticInfo->val_type);
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
        else if (match_with_var(node,3,EXP,AND,EXP)==1)
        {
            //这里思考如下：
            //首先如果2个均是数值，那就比较是否可以直接计算
            //如果其中存在id变量，此时需要查找hashtalbe,需要注意，基于LR分析为最左规约，每次寻找最左直接短语规约，必然，如果变量有定义，那么就要
            //会在hashtable中存在，反之，可以说明使用了未定义的变量，如果存在，必然拥有对应的type,则可以比较是否存在type不一致问题

            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }  
        else if (match_with_var(node,3,EXP,OR,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,EQ,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,NEQ,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,LT,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,LE,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,GT,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,GE,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,PLUS,EXP)==1)
        {
            printf("aaaa");
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,MINUS,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,STAR,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,EXP,DIV,EXP)==1)
        {
            if(check_on_logic_caculate(hashtable,node,child1,child3)==1){
                //检查通过
                node->SemanticInfo->val_type=child1->SemanticInfo->val_type;
            }
            else{
                node->SemanticInfo->val_type=SVT_ERROR;
            }
        }
        else if (match_with_var(node,3,LP,EXP,RP)==1)
        {
            node->SemanticInfo->val_type=child2->SemanticInfo->val_type;
        }
        else if (match_with_var(node,3,EXP,DOT,ID)==1)
        {
            SemanticInfo_ptr p=hash_table_lookup(hashtable,child1->SemanticInfo->name);
            if (!p)
            {
                reporterror(node->linenum,UndefinedStruct,"Member access on non-struct,you can noly use '.' on struct type variable");
            }
            else
            {
                int flag=0;
                printf("[exp on struct access]:%s\n",p->name);
                printf("[exp on struct access]:%d\n",p->isstruct);
                if (p->isstruct==0)
                {
                    reporterror(node->linenum,UndefinedStruct,"Member access on non-struct,you can noly use '.' on struct type variable");
                }
                else if (p->isstruct==1)
                {
                    for (int  i = 0; i < p->semanticmuldefinfo->type_count; i++)
                    {
                        TypeEntry_ptr entry=p->semanticmuldefinfo->entries[i];
                        printf("#%d\n",entry->type);
                        for (int j = 0; j < entry->var_count; j++)
                        {
                            if (strcmp(entry->var_names[j],child3->ID)==0)
                            {
                                flag=1;
                            }
                        }
                    }
                    if (flag==0)
                    {
                        reporterror(node->linenum,UndefinedStructMember,"can not find member on struct");
                    }
                    else
                    {
                        node->SemanticInfo=p;
                    }
                    
                }
            }
        } 
    }   
    else if (node->child_count=4)
    {
        TreeNode_ptr child1=node->children[0];
        TreeNode_ptr child2=node->children[1];
        TreeNode_ptr child3=node->children[2];
        TreeNode_ptr child4=node->children[3];
        //function
        if (match_with_var(node,4,ID,LP,ARGS,RP))
        {
            SemanticInfo_ptr func=hash_table_lookup(hashtable,child1->ID);
            
            if (!func||((func->isfunction==0)&&(func->isID==0)))
            {
                reporterror(node->linenum,UndefinedFunctionCalled,"can not use undefined function");
            }
            else if (func->isID==1)
            {
                reporterror(node->linenum,FunctionCalledOnNonFunction,"can not application a function type on a varible type");
            }
            else
            {
                int args_number=func->semanticFunctioninfo->val_number;
                
                SemanticFunctionInfo_ptr fun=func->semanticFunctioninfo;
                SemanticFunctionInfo_ptr p=child3->SemanticInfo->semanticFunctioninfo;
                printf("EXP_ARGS : %d %d",args_number,p->val_number);
                if (args_number!=p->val_number)
                {
                    reporterror(node->linenum,ParameterListMismatch,"miss match with function args number");
                }
                
                for(int i=0;i<args_number;i++){
                    if (fun->val_type[i]!=p->val_type[i])
                    {
                        reporterror(node->linenum,ParameterListMismatch,"miss match with function args type");
                    }
                    else if (fun->val_type[i]==p->val_type[i])
                    {
                        continue;
                    }
                }  
            }
            node->SemanticInfo=func;
        }
        else if (match_with_var(node,4,EXP,LB,EXP,RB))
        {
            ///意味着这必然是一个数组访问
            // TreeNode_ptr child1
            SemanticInfo_ptr p1=hash_table_lookup(hashtable,child1->SemanticInfo->name);
            SemanticInfo_ptr p2=child3->SemanticInfo;
            if (p1->isArray==0)
            {
                reporterror(node->linenum,ArrayAccessOnNonArray,"can not application array on a none array type varible");
            }
            else
            {
                if (p2->val_type!=SVT_INT)
                {
                    reporterror(node->linenum,ArrayIndexTypeMismatch,"can only access to array with integer index");
                }
            }
            
        }
    }
    return;
}

void SetHashTable_Args(HashTable_ptr hashtable,TreeNode_ptr node){
    printf("ARGS");
    if (node->child_count==3)
    {
        if (match_with_var(node,3,EXP,COMMA,ARGS)==1)
        {
            TreeNode_ptr child1=node->children[0];
            TreeNode_ptr child2=node->children[2];
            SemanticFunctionInfo_ptr p=child2->SemanticInfo->semanticFunctioninfo;
            p->val_number+=1;
            p->val_name=realloc(p->val_name,p->val_number*sizeof(char*));
            p->val_type=realloc(p->val_type,p->val_number*sizeof(int));
            p->val_name[p->val_number-1]=child1->SemanticInfo->name;
            p->val_type[p->val_number-1]=child2->SemanticInfo->val_type;
            node->SemanticInfo->semanticFunctioninfo=p;
        }
    }
    else if (node->child_count==1)
    {
        if (match_with_var(node,1,EXP)==1)
        {
            TreeNode_ptr child=node->children[0];
            ///由于args只会在调用函数时使用，所以我这里偷个懒，直接使用semanticfunctinoinfo了
            SemanticFunctionInfo_ptr p=malloc(sizeof(SemanticFunctionInfo));
            p->val_number=1;
            p->val_name=malloc(p->val_number*sizeof(char*));
            p->val_type=malloc(p->val_number*(sizeof(int)));
            p->val_name[0]=child->SemanticInfo->name;
            p->val_type[0]=child->SemanticInfo->val_type;
            node->SemanticInfo->semanticFunctioninfo=p;
        }
    }
    
    
    //这里的exp可能是id，也可能是int,float,需要记录
    
}




//注意参数传递顺序应当与产生式一致
int match_with_var(TreeNode_ptr node,int child_num,...){
    va_list args;
    // int flag=1;
    va_start(args,child_num);
    for (int i=0;i<child_num;i++){
        int arg=va_arg(args,int);
        // printf("%d\n",arg);
        // printf("%d\n",node->children[i]->token);
        // flag=(node->children[i]->token==arg)?1:0;
        if (node->children[i]->token!=arg)
        {
            return 0;
        }
    }
    va_end(args);
    return 1;
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
    else if (node1->SemanticInfo->isID==0&&node2->SemanticInfo->isID!=0)
    {
        SemanticInfo_ptr p=hash_table_lookup(hashtable,node2->SemanticInfo->name);
        if (p==NULL)
        {
            reporterror(father->linenum,UndefinedVariable,"error undefined variable,can not use undefined variable to caculate");  
            return 0;
        }
        else
        {
            if (p->val_type!=node1->SemanticInfo->val_type)
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
TypeEntry_ptr find_type_entry(SemanticmuldefInfo_ptr s, int target_type) {
    for (int i = 0; i < s->type_count; i++) {
        if (s->entries[i]->type == target_type) {
            return s->entries[i]; // 找到匹配类型
        }
    }
    return NULL; // 未找到
}