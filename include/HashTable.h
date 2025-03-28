/*
 * @Author: Peter/peterluck2021@163.com
 * @Date: 2025-03-27 17:02:02
 * @LastEditors: Peter/peterluck2021@163.com
 * @LastEditTime: 2025-03-27 20:39:18
 * @FilePath: /Lab/include/HashTable.h
 * @Description: hashtable error
 * 
 * Copyright (c) 2025 by peterluck2021@163.com, All Rights Reserved. 
 */
#include "SemanticInfo.h"
// 哈希表节点结构体
typedef struct HashNode {
    int key;                // token（键）
    SemanticInfo_ptr value;     // 语义信息（值）
    struct HashNode* next;  // 链表解决哈希冲突
} HashNode;

// 哈希表结构体
typedef struct {
    HashNode** buckets;  // 桶数组
    int size;            // 桶的数量
    int count;           // 当前元素数量（可选）
} HashTable;

typedef HashTable* HashTable_ptr;
typedef HashNode* HashNode_ptr;

HashTable_ptr create_hash_table(int size);
void hash_table_insert(HashTable_ptr table, SemanticInfo_ptr value);
SemanticInfo_ptr hash_table_lookup(HashTable_ptr table, int key);
void destroy_hash_table(HashTable_ptr table);
