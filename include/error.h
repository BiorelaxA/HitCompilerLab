/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-24 15:40:02
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-28 16:22:37
 * @FilePath: /Lab/include/error.h
 * @Description: error.h file
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

#if !defined(ERROR_H)
#define ERROR_H


#include "../include/TreeNode.h"
void readError(TreeNode_ptr error);
extern int has_error;
void reporterror(int linenum,int errortype,char* error);

typedef enum ErrorType_e{
    LEXICAL_ERROR_BASE = 0,

    UnrecognizedCharacter=1,
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

    UndefinedVariable=18,          // Error 1
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

char ErrorNames[UNDEF_SEMANTIC_ERROR-LEXICAL_ERROR_BASE+1][50]={
    "LEXICAL_ERROR_BASE",
    "UnrecognizedCharacter",
    "InvalidIdentifier",
    "InvalidNumber",
    "InvalidFloat",
    "UNDEF_LEXICAL_ERROR",
    "SYNTAX_ERROR_BASE",
    "UnexpectedStatement",
    "UnexpectedDeclaration",
    "MissingSemicolon",
    "MissingRightBracket",
    "MissingRightParenthesis",
    "MissingComma",
    "MissingSpecifier",
    "UnterminatedComment",
    "UnexpectedExpression",
    "UNDEF_SYNTAX_ERROR",
    "SEMANTIC_ERROR_BASE",
    "UndefinedVariable",
    "UndefinedFunctionCalled",
    "VariableNameRedefinition",
    "FunctionRedefinition",
    "AssignmentTypeMismatch",
    "AssignToRvalue",
    "OperatorTypeMismatch",
    "ReturnTypeMismatch",
    "ParameterListMismatch",
    "ArrayAccessOnNonArray",
    "FunctionCalledOnNonFunction",
    "ArrayIndexTypeMismatch",
    "MemberAccessOnNonStruct",
    "UndefinedStructMember",
    "InvalidMemberDefinition",
    "ConflictStructDefinition",
    "UndefinedStruct",
    "UndefinedExternalFunction",
    "ImplicitFunctionDeclaration",
    "UNDEF_SEMANTIC_ERROR"
}





#endif // ERROR_H
