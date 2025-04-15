/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-29 00:17:18
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-04-15 16:04:42
 * @FilePath: /Lab/include/CmmparserTypes.h
 * @Description: CmmparserTypes.h
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

#ifndef CMMPARSERTYPES_H
#define CMMPARSERTYPES_H

#include <stdio.h>
void readError(int linenum,int issemanticValue);
extern int has_error;
void reporterror(int linenum,int errortype,char* error);

typedef enum ErrorType_e{
    LEXICAL_ERROR_BASE = 0,

    UnrecognizedCharacter=18,
    InvalidIdentifier=2,
    InvalidNumber=3,
    InvalidFloat=4,

    UNDEF_LEXICAL_ERROR = 5,

    SYNTAX_ERROR_BASE = 6,

    UnexpectedStatement=7,
    UnexpectedDeclaration=8,
    MissingSemicolon=9,
    MissingRightBracket=10,
    MissingRightParenthesis=11,
    MissingComma=12,
    MissingSpecifier=13,
    UnterminatedComment=14,
    UnexpectedExpression=15,

    UNDEF_SYNTAX_ERROR = 16,

    SEMANTIC_ERROR_BASE = 17,

    UndefinedVariable=1,          // Error 1
    UndefinedFunctionCalled=19,    // Error 2
    VariableNameRedefinition=20,       // Error 3
    FunctionRedefinition=21,       // Error 4
    AssignmentTypeMismatch=23,     // Error 5
    AssignToRvalue=24,             // Error 6
    OperatorTypeMismatch=25,       // Error 7
    ReturnTypeMismatch=26,         // Error 8
    ParameterListMismatch=27,      // Error 9
    ArrayAccessOnNonArray=28,      // Error 10
    FunctionCalledOnNonFunction=29,// Error 11
    ArrayIndexTypeMismatch=30,     // Error 12
    MemberAccessOnNonStruct=31,    // Error 13
    UndefinedStructMember=32,      // Error 14
    InvalidMemberDefinition=33,    // Error 15
    ConflictStructDefinition=34,   // Error 16
    UndefinedStruct=35,            // Error 17
    UndefinedExternalFunction=36,  // Error 18
    ImplicitFunctionDeclaration=37,// Error 19

    UNDEF_SEMANTIC_ERROR = 38,
}ErrorType;

// char ErrorNames[UNDEF_SEMANTIC_ERROR-LEXICAL_ERROR_BASE+1][50]={
//     "LEXICAL_ERROR_BASE",
//     "UnrecognizedCharacter",
//     "InvalidIdentifier",
//     "InvalidNumber",
//     "InvalidFloat",
//     "UNDEF_LEXICAL_ERROR",
//     "SYNTAX_ERROR_BASE",
//     "UnexpectedStatement",
//     "UnexpectedDeclaration",
//     "MissingSemicolon",
//     "MissingRightBracket",
//     "MissingRightParenthesis",
//     "MissingComma",
//     "MissingSpecifier",
//     "UnterminatedComment",
//     "UnexpectedExpression",
//     "UNDEF_SYNTAX_ERROR",
//     "SEMANTIC_ERROR_BASE",
//     "UndefinedVariable",
//     "UndefinedFunctionCalled",
//     "VariableNameRedefinition",
//     "FunctionRedefinition",
//     "AssignmentTypeMismatch",
//     "AssignToRvalue",
//     "OperatorTypeMismatch",
//     "ReturnTypeMismatch",
//     "ParameterListMismatch",
//     "ArrayAccessOnNonArray",
//     "FunctionCalledOnNonFunction",
//     "ArrayIndexTypeMismatch",
//     "MemberAccessOnNonStruct",
//     "UndefinedStructMember",
//     "InvalidMemberDefinition",
//     "ConflictStructDefinition",
//     "UndefinedStruct",
//     "UndefinedExternalFunction",
//     "ImplicitFunctionDeclaration",
//     "UNDEF_SEMANTIC_ERROR"
// };
struct SemanticFunctionInfo
{
    int val_number;
    //below number must be val_number
    int* val_type;      // 动态数组指针
    char** val_name;     // 动态字符串数组指针
};
typedef struct SemanticFunctionInfo SemanticFunctionInfo;
typedef struct SemanticFunctionInfo* SemanticFunctionInfo_ptr;

// 每个类型对应的变量信息
typedef struct {
    int type;           // 类型标识符 (可以用枚举或实际类型码表示)
    int var_count;      // 该类型对应的变量数量
    char** var_names;   // 该类型对应的变量名数组 (char* 数组)
} TypeEntry;
typedef TypeEntry* TypeEntry_ptr;
// 语义分析结构体信息
typedef struct SemanticmuldefInfo {
    int type_count;     // 类型条目数量 (如示例中的2种类型)
    TypeEntry** entries; // 类型条目数组 (每个元素存储一种类型的信息)
} SemanticmuldefInfo;

typedef SemanticmuldefInfo* SemanticmuldefInfo_ptr;

struct SemanticArrayInfo{
    int val_type;
    int row_number;
    int column_number;
};
typedef struct SemanticArrayInfo SemanticArrayInfo;
typedef struct SemanticArrayInfo* SemanticArrayInfo_ptr;

// struct SemanticIDDefInfo{
//     /// @brief 每个类型定义的变量个数
//     int number;
//     // /// @brief 每个定义的种类
//     // int* val_type;
//     /// @brief 每个定义的name字面量
//     char** val_name;
// };
// typedef struct SemanticIDDefInfo SemanticIDDefInfo;
// typedef struct SemanticIDDefInfo* SemanticIDDefInfo_ptr;

struct SemanticInfo
{
    ///lex_yy.c生成的id表,当然还应该包括syntax.tab.c中非终结符的id
    int Type_id;
    // // 是否是int/float可以参与计算
    // int isValue;
    int issemanticValue;
    char* name;
    //这里的变量类型只能在非function,struct,array时定义，否则为0
    //只有在定义之后才能使用
    int isdefined;//判断是否定义了
    int val_type;
    int isfunction;
    /// @brief 用于控制下面的muldef是单独只是多个定义还是属于结构体的多个定义
    int isstruct;
    int isArray;
    int isID;
    /// @brief 用于控制下面是否有多个定义的，例如：int a,b,c;这类用于控制SemanticIDDefInfo是否有效
    int ismulidef;
    // SemanticIDDefInfo_ptr semanticiddefinfo;
    SemanticFunctionInfo_ptr semanticFunctioninfo;
    SemanticmuldefInfo_ptr semanticmuldefinfo;
    SemanticArrayInfo_ptr semanticarrayinfo;
};
typedef struct SemanticInfo SemanticInfo;
typedef struct SemanticInfo* SemanticInfo_ptr;
typedef struct HashNode {
    char* key;                // token（键）
    SemanticInfo_ptr value;     // 语义信息（值）
    struct HashNode* next;  // 链表解决哈希冲突
} HashNode;
typedef HashNode* HashNode_ptr;

// 哈希表结构体
typedef struct {
    HashNode_ptr* buckets;  // 桶数组
    int size;            // 桶的数量
    int count;           // 当前元素数量（可选）
} HashTable;
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
typedef struct TreeNode TreeNode;
typedef struct TreeNode* TreeNode_ptr;


typedef HashTable* HashTable_ptr;

extern HashTable_ptr GLOBAL_HASH_TABLE;

HashTable_ptr create_hash_table(int size);
void hash_table_insert(HashTable_ptr table, SemanticInfo_ptr value);
SemanticInfo_ptr hash_table_lookup(HashTable_ptr table, char* key);
void destroy_hash_table(HashTable_ptr table);
void SetHashTable(HashTable_ptr hashtable,TreeNode_ptr node);
SemanticInfo_ptr create_semanticinfo(int issemanticValue,int token);
// void SetHashTable(HashTable_ptr hashtable,TreeNode_ptr node);
// void SemanticAnalyzer(TreeNode_ptr father);
// #include "HashTable.h"
// #include "TreeNode.h"
typedef enum SemanticType{
    SVT_INT =1,
    SVT_FLOAT=2,
    SVT_VOID=0,
    SVT_STRUCT=3,
    SVT_ERROR=-1,
}SemanticType;


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


TreeNode_ptr create_node(int token, int linenum,int child_count,int issemanticValue);
void add_children(TreeNode_ptr father,int child_num,...);
void set_root_node(TreeNode_ptr node);
const char* get_semantic_name(int token);
const char* get_token_name(int token);
void test_print(TreeNode_ptr node,int depth,FILE* output);
TreeNode_ptr getrootnode();
void free_tree(TreeNode_ptr node);

typedef struct {
    char **data;     // 动态数组存储字符串指针
    int top;         // 栈顶索引（初始为 -1）
    int capacity;    // 当前容量
} StringStack;
typedef StringStack* StringStack_ptr;
StringStack_ptr create_stack(int initial_capacity);
int push(StringStack_ptr stack, const char *str);
char* pop(StringStack_ptr stack);
const char* peek(const StringStack_ptr stack);
int is_empty(const StringStack_ptr stack);
void destroy_stack(StringStack_ptr stack);

extern StringStack_ptr Function_Stack;

#endif // CMMPARSERTYPES_H
