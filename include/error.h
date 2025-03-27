/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-24 15:40:02
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 17:10:35
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

typedef enum ErrorType_e{
    LEXICAL_ERROR_BASE = 0,

    UnrecognizedCharacter,
    InvalidIdentifier,
    InvalidNumber,
    InvalidFloat,

    UNDEF_LEXICAL_ERROR = 49,

    SYNTAX_ERROR_BASE = 50,

    UnexpectedStatement,
    UnexpectedDeclaration,
    MissingSemicolon,
    MissingRightBracket,
    MissingRightParenthesis,
    MissingComma,
    MissingSpecifier,
    UnterminatedComment,
    UnexpectedExpression,

    UNDEF_SYNTAX_ERROR = 99,

    SEMANTIC_ERROR_BASE = 100,

    UndefinedVariable,          // Error 1
    UndefinedFunctionCalled,    // Error 2
    VariableNameRedefinition,       // Error 3
    FunctionRedefinition,       // Error 4
    AssignmentTypeMismatch,     // Error 5
    AssignToRvalue,             // Error 6
    OperatorTypeMismatch,       // Error 7
    ReturnTypeMismatch,         // Error 8
    ParameterListMismatch,      // Error 9
    ArrayAccessOnNonArray,      // Error 10
    FunctionCalledOnNonFunction,// Error 11
    ArrayIndexTypeMismatch,     // Error 12
    MemberAccessOnNonStruct,    // Error 13
    UndefinedStructMember,      // Error 14
    InvalidMemberDefinition,    // Error 15
    ConflictStructDefinition,   // Error 16
    UndefinedStruct,            // Error 17
    UndefinedExternalFunction,  // Error 18
    ImplicitFunctionDeclaration,// Error 19

    UNDEF_SEMANTIC_ERROR = 149,
}ErrorType;





#endif // ERROR_H
