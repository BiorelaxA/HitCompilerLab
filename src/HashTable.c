#include <stdio.h>
#include <stdlib.h>

// 假设文法符号的语义信息结构体
typedef struct {
    int type;       // 符号类型
    char* name;     // 符号名称
    // 可添加其他字段
} SemanticInfo;

// 哈希表节点结构体
typedef struct HashNode {
    int key;                // token（键）
    SemanticInfo value;     // 语义信息（值）
    struct HashNode* next;  // 链表解决哈希冲突
} HashNode;

// 哈希表结构体
typedef struct {
    HashNode** buckets;  // 桶数组
    int size;            // 桶的数量
    int count;           // 当前元素数量（可选）
} HashTable;

// 哈希函数：根据键计算桶的索引
int hash_function(int key, int table_size) {
    return key % table_size;
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

// 插入键值对（如果存在则更新值）
void hash_table_insert(HashTable* table, int key, SemanticInfo value) {
    int index = hash_function(key, table->size);
    HashNode* current = table->buckets[index];

    // 检查是否已存在相同key
    while (current) {
        if (current->key == key) {
            current->value = value;  // 更新值
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

// 删除键值对
void hash_table_delete(HashTable* table, int key) {
    int index = hash_function(key, table->size);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;

    while (current) {
        if (current->key == key) {
            if (prev) {
                prev->next = current->next;
            } else {
                table->buckets[index] = current->next;
            }
            free(current);
            table->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

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

// 示例用法
int main() {
    // 创建哈希表（桶数量为10）
    HashTable* table = create_hash_table(10);
    if (!table) {
        fprintf(stderr, "Failed to create hash table.\n");
        return 1;
    }

    // 插入数据
    SemanticInfo info1 = {1, "variable"};
    SemanticInfo info2 = {2, "function"};
    hash_table_insert(table, 1001, info1);
    hash_table_insert(table, 2002, info2);

    // 查找数据
    SemanticInfo* result = hash_table_lookup(table, 1001);
    if (result) {
        printf("Found: type=%d, name=%s\n", result->type, result->name);
    }

    // 删除数据
    hash_table_delete(table, 2002);

    // 释放哈希表内存
    destroy_hash_table(table);
    return 0;
}