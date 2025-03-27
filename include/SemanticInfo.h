/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 16:18:47
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 16:54:25
 * @FilePath: /Lab/include/SemanticInfo.h
 * @Description: SemanticInfo.h file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

/// @brief the struct for each semantic symbol to store semantic information
/// should include the semantic_type(int).value(only int or float can caculate),
/// name for value(we can not renames),
struct SemanticInfo
{
    ///lex_yy.c生成的id表,当然还应该包括syntax.tab.c中非终结符的id
    int Type_id;
    // // 是否是int/float可以参与计算
    // int isValue;
    char* name;

};
typedef struct SemanticInfo SemanticInfo;
typedef struct SemanticInfo* SemanticInfo_ptr;


SemanticInfo_ptr create_semanticinfo(int type_id,char* name);
