/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-29 23:04:03
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-29 23:07:26
 * @FilePath: /Lab/src/Stack.c
 * @Description: 
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */

 #include "../include/CmmparserTypes.h"
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 StringStack_ptr create_stack(int initial_capacity) {
    StringStack_ptr stack = (StringStack_ptr)malloc(sizeof(StringStack));
    if (!stack) return NULL;

    stack->data = (char**)malloc(initial_capacity * sizeof(char*));
    if (!stack->data) {
        free(stack);
        return NULL;
    }

    stack->top = -1;
    stack->capacity = initial_capacity;
    return stack;
}
int push(StringStack_ptr stack, const char *str) {
    if (stack->top == stack->capacity - 1) {
        // 容量不足，扩容为双倍
        int new_capacity = stack->capacity * 2;
        char **new_data = (char**)realloc(stack->data, new_capacity * sizeof(char*));
        if (!new_data) return 0;  // 扩容失败

        stack->data = new_data;
        stack->capacity = new_capacity;
    }

    // 深拷贝字符串
    char *copy = strdup(str);
    if (!copy) return 0;  // 内存分配失败

    stack->data[++stack->top] = copy;
    return 1;
}
char* pop(StringStack_ptr stack) {
    if (stack->top == -1) return NULL;  // 栈空

    char *str = stack->data[stack->top];
    stack->data[stack->top--] = NULL;  // 清空引用
    return str;  // 调用者需负责释放返回的字符串内存
}
const char* peek(const StringStack_ptr stack) {
    if (stack->top == -1) return NULL;
    return stack->data[stack->top];
}
int is_empty(const StringStack_ptr stack) {
    return stack->top == -1;
}
void destroy_stack(StringStack_ptr stack) {
    if (!stack) return;

    // 释放所有字符串
    for (int i = 0; i <= stack->top; i++) {
        free(stack->data[i]);
    }

    free(stack->data);
    free(stack);
}