#include <stdio.h>
#include <stdlib.h>
#include "../include/CmmparserTypes.h"
#include <string.h>
// 哈希函数：根据键计算桶的索引
//建议使用指导书中的，这样冲突少
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

HashTable_ptr create_hash_table(int size) {
    // 1. 分配哈希表主体内存
    HashTable_ptr table = (HashTable_ptr)malloc(sizeof(HashTable));
    if (!table) return NULL;

    // 2. 分配桶数组（每个桶是一个 HashNode 链表头）
    table->buckets = (HashNode_ptr*)malloc(size * sizeof(HashNode_ptr));
    if (!table->buckets) {
        free(table);
        return NULL;
    }

    // 3. 初始化桶数组为空链表
    memset(table->buckets, 0, size * sizeof(HashNode_ptr));

    // 4. 初始化元数据
    table->size = size;
    table->count = 0;

    return table;
}

/// 插入键值对（如果存在则更新值）
///u如果是多个定义的变量则插入多个，如果是一个函数包含多个参数，则之插入一个
/// 这里不用考虑ismulidef
void hash_table_insert(HashTable* table, SemanticInfo_ptr value) {
    // if (value->ismulidef==0)
    // {
    int index = hash_map(value->name);

    printf("[hash_table_insert]:%s\n",value->name);
    //token的数值存入token
    char* key=value->name;
    HashNode_ptr current = table->buckets[index];

    // 检查是否已存在相同key,直到查完
    while (current) {
        if (current->key == key) {
            //todo printerror
            // printf("1");
            return;
        }
        current = current->next;
    }

    // 创建新节点并插入链表头部
    HashNode_ptr new_node = malloc(sizeof(HashNode));
    if (!new_node) return;

    new_node->key = key;
    // printf("[hash_table_insert]insert finish:%s\n",new_node->key);
    new_node->value = value;
    new_node->next = table->buckets[index];
    table->buckets[index] = new_node;
    table->count++;
    // }
    // else
    // {
    //     for (int  i = 0; i < value->semanticmuldefinfo->number; i++)
    //     {
    //         int index = hash_map(value->semanticiddefinfo->val_name[i]);
    //         // printf("[hash_table_insert]:%d\n",index);
    //         //token的数值存入token
    //         char* key=value->semanticiddefinfo->val_name[i];
    //         HashNode_ptr current = table->buckets[index];

    //         // 检查是否已存在相同key,直到查完
    //         while (current) {
    //             if (current->key == key) {
    //                 //todo printerror
    //                 // printf("1");
    //                 return;
    //             }
    //             current = current->next;
    //         }

    //         // 创建新节点并插入链表头部
    //         HashNode_ptr new_node = malloc(sizeof(HashNode));
    //         if (!new_node) return;

    //         new_node->key = key;
    //         // printf("[hash_table_insert]insert finish:%s\n",new_node->key);
    //         new_node->value = value;
    //         new_node->next = table->buckets[index];
    //         table->buckets[index] = new_node;
    //         table->count++;
    //     }
    // }
    // // printf("[hash_table_insert]:%s\n",value->name);
    // int index = hash_map(value->name);
    // // printf("[hash_table_insert]:%d\n",index);
    // //token的数值存入token
    // char* key=value->name;
    // HashNode_ptr current = table->buckets[index];

    // // 检查是否已存在相同key,直到查完
    // while (current) {
    //     if (current->key == key) {
    //         //todo printerror
    //         // printf("1");
    //         return;
    //     }
    //     current = current->next;
    // }

    // // 创建新节点并插入链表头部
    // HashNode_ptr new_node = malloc(sizeof(HashNode));
    // if (!new_node) return;

    // new_node->key = key;
    // // printf("[hash_table_insert]insert finish:%s\n",new_node->key);
    // new_node->value = value;
    // new_node->next = table->buckets[index];
    // table->buckets[index] = new_node;
    // table->count++;
    // // SemanticInfo_ptr a=hash_table_lookup(table,value->name);
    // // printf("[hash_table_insert]insert lookup:%s\n",value->name);
}

// 查找键对应的值（返回指针，未找到返回NULL）
SemanticInfo_ptr hash_table_lookup(HashTable_ptr table, char* name) {
    printf("[hash_table_lookup]:%s\n",name);
    int index = hash_map(name);
    // printf("[hash_table_lookup]:%d\n",table->count);
    // printf("zzzzzzzzz");
    // printf("[hash_table_lookup]:%d\n",index);
    // printf("dddddddddddd");
    HashNode_ptr current = table->buckets[index];
    // printf("[hash_table_lookup]:%s\n",current->key);
    // printf("fsjofe");
    while (current!=NULL){
        // printf("2222");
        if (strcmp(current->key,name)==0) {
            // printf("[hash_table_lookup]finish:%s\n",current->key);
            return current->value;
        }
        // printf("3333");
        printf("%s",current->key);
        current = current->next;
    }
    // printf("[hash_table_lookup]exit with null");
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