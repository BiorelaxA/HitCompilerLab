#include <stdio.h>
#include <stdlib.h>
#include "../include/SemanticInfo.h"
#include "../include/HashTable.h"

// 哈希函数：根据键计算桶的索引
//todo 建议使用指导书中的，这样冲突少
int hash_map(char* name){
    int val=0;
    int i;
    for (;*name;++name){
        val=(val<<2)+*name;
        if (i=val&~0x5f)
        {
            val=(val^(i>>12))&0x5f;
        }
    }
    return val;
}

// 创建哈希表
HashTable* create_hash_table(int size) {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (!table) return NULL;

    table->size = size;
    table->count = 0;
    table->buckets = (HashNode**)calloc(size, sizeof(HashNode*));
    if (!table->buckets) {
        free(table);
        return NULL;
    }
    return table;
}

/// 插入键值对（如果存在则更新值）
void hash_table_insert(HashTable* table, SemanticInfo_ptr value) {
    int index = hash_map(value->name);
    //token的数值存入token
    int key=value->Type_id;
    HashNode* current = table->buckets[index];

    // 检查是否已存在相同key,直到查完
    while (current) {
        if (current->key == key) {
            //todo printerror
            return;
        }
        current = current->next;
    }

    // 创建新节点并插入链表头部
    HashNode* new_node = (HashNode*)malloc(sizeof(HashNode));
    if (!new_node) return;

    new_node->key = key;
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;
}

// 查找键对应的值（返回指针，未找到返回NULL）
SemanticInfo* hash_table_lookup(HashTable* table, int key) {
    int index = hash_function(key, table->size);
    HashNode* current = table->buckets[index];

    while (current) {
        if (current->key == key) {
            return &(current->value);
        }
        current = current->next;
    }
    return NULL;
}

//大概率用不到
// // 删除键值对
// void hash_table_delete(HashTable* table, int key) {
//     int index = hash_function(key, table->size);
//     HashNode* current = table->buckets[index];
//     HashNode* prev = NULL;

//     while (current) {
//         if (current->key == key) {
//             if (prev) {
//                 prev->next = current->next;
//             } else {
//                 table->buckets[index] = current->next;
//             }
//             free(current);
//             table->count--;
//             return;
//         }
//         prev = current;
//         current = current->next;
//     }
// }

// 销毁哈希表（释放所有内存）
void destroy_hash_table(HashTable* table) {
    if (!table) return;

    for (int i = 0; i < table->size; i++) {
        HashNode* current = table->buckets[i];
        while (current) {
            HashNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(table->buckets);
    free(table);
}