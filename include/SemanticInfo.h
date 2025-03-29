/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 16:18:47
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-29 13:34:32
 * @FilePath: /Lab/include/SemanticInfo.h
 * @Description: 
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
// /*
//  * @Author: Peter/peterluck2021@163.com
//  * @Date: 2025-03-27 16:18:47
//  * @LastEditors: Peter/peterluck2021@163.com
//  * @LastEditTime: 2025-03-29 10:34:41
//  * @FilePath: /Lab/include/SemanticInfo.h
//  * @Description: SemanticInfo.h file
//  * 
//  * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
//  */

// /// @brief the struct for each semantic symbol to store semantic information
// /// should include the semantic_type(int).value(only int or float can caculate),
// /// name for value(we can not renames),

// #ifndef SEMANTICINFO_H
// #define SEMANTICINFO_H

// // #include "HashTable.h"
// // #include "TreeNode.h"
// // struct TreeNode;
// // typedef struct TreeNode* TreeNode_ptr; 
// // struct HashTable;
// // typedef struct HashTable* HashTable_ptr; 



// struct SemanticFunctionInfo
// {
//     int val_number;
//     //below number must be val_number
//     int* val_type;      // 动态数组指针
//     char** val_name;     // 动态字符串数组指针
// };
// typedef struct SemanticFunctionInfo SemanticFunctionInfo;
// typedef struct SemanticFunctionInfo* SemanticFunctionInfo_ptr;

// struct SemanticStructInfo{
//     int val_number;
//     int* val_type;
//     char** val_name;
// };
// typedef struct SemanticStructInfo SemanticStructInfo;
// typedef struct SemanticStructInfo* SemanticStructInfo_ptr;

// struct SemanticArrayInfo{
//     int* val_type;
//     int row_number;
//     int column_number;
// };
// typedef struct SemanticArrayInfo SemanticArrayInfo;
// typedef struct SemanticArrayInfo* SemanticArrayInfo_ptr;
// struct SemanticInfo
// {
//     ///lex_yy.c生成的id表,当然还应该包括syntax.tab.c中非终结符的id
//     int Type_id;
//     // // 是否是int/float可以参与计算
//     // int isValue;
//     int issemanticValue;
//     char* name;
//     //这里的变量类型只能在非function,struct,array时定义，否则为0
//     //只有在定义之后才能使用
//     int isdefined;//判断是否定义了
//     int val_type;
//     int isfunction;
//     int isstruct;
//     int isArray;
//     int isID;
//     SemanticFunctionInfo_ptr semanticFunctioninfo;
//     SemanticStructInfo_ptr semanticstructinfo;
//     SemanticArrayInfo_ptr semanticarrayinfo;
// };
// typedef struct SemanticInfo SemanticInfo;
// typedef struct SemanticInfo* SemanticInfo_ptr;

// SemanticInfo_ptr create_semanticinfo(int issemanticValue,int token);
// // void SetHashTable(HashTable_ptr hashtable,TreeNode_ptr node);
// // void SemanticAnalyzer(TreeNode_ptr father);
// // #include "HashTable.h"
// // #include "TreeNode.h"
// typedef enum SemanticType{
//     SVT_INT =1,
//     SVT_FLOAT=2,
//     SVT_VOID=0,
//     SVT_STRUCT=3,
//     SVT_ERROR=-1,
// }
// #endif // SEMANTICINFO_H