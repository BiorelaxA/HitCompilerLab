struct meta_data {
    void (*dtor)(void*);
    void* data;
};
// 从data的位置往前移动到struct meta_data的开始位置
static struct meta_data* get_meta(void* ptr) {
    return ptr - sizeof(struct meta_data);
}
__attribute__((malloc))
void* smart_malloc(size_t size, void(*dtor)(void*)) {
    // 一次性分配好struct meta_data的大小和需要分配的大小
    struct meta_data* mdata = malloc(sizeof(struct meta_date) + size);

    // 初始化
    *mdata = (struct meta_data) {
        .dtor = dtor,
        .data = mdata + 1 // 加1实际上是 1 = sizeof( struct meta_data )
    };

    return mdata->data;
}
void smart_free(void* data) {
    if( data == NULL ) return;

    data = *(void**)data;
    if( data == NULL ) return;

    struct meta_data* mdata = get_meta(data);
    assert( data == mdata->data);

    if( mdata->dtor ) {
            mdata->dtor( data );
    }
    free(mdata);
}

// usage
#define auto_free __attribute__ ((cleanup(smart_free)))