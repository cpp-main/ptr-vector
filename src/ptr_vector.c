/**
 * File: ptr_vector.c
 *
 * PtrVector容器的函数实现
 *
 * Change Logs:
 * Date         Author      Notes
 * 2016-04-07   Sid lee     Create
 */
#include <string.h>
#include <assert.h>
#include "ptr_vector.h"

#define _DEFAULT_INIT_SIZE 32

struct PtrVector {
    void** array_ptr;   //! 指针数组指针
    size_t array_capacity;  //! 指针数组容量
    int    array_num;  //! 成员个数
};

///////////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////////

PtrVector* PtrVector_Create(size_t reserved_size) {
    assert(reserved_size >= 0);
    PtrVector* vec = calloc(1, sizeof(PtrVector));
    if (vec != NULL) {
        int init_size = (reserved_size != 0) ? reserved_size : _DEFAULT_INIT_SIZE;
        void ** ptr = calloc(init_size, sizeof(void*));
        if (ptr != NULL) {
            vec->array_ptr = ptr;
            vec->array_capacity = init_size;
            vec->array_num = 0;
        } else {
            free(vec);
            vec = NULL;
        }
    }
    return vec;
}

PtrVector* PtrVector_Clone(const PtrVector* src) {
    assert(src != NULL);
    PtrVector* vec = calloc(1, sizeof(PtrVector));
    if (vec != NULL) {
        void** ptr = calloc(src->array_capacity, sizeof(void*));
        if (ptr != NULL) {
            vec->array_ptr = ptr;
            vec->array_capacity = src->array_capacity;
            vec->array_num = src->array_num;
            memcpy(vec->array_ptr, src->array_ptr, (sizeof(void*) * src->array_num));
        } else {
            free(vec);
            vec = NULL;
        }
    }
    return vec;
}

size_t PtrVector_Size(const PtrVector* vec) {
    assert(vec != NULL);
    return vec->array_num;
}

size_t PtrVector_Capacity(const PtrVector* vec) {
    assert(vec != NULL);
    return vec->array_capacity;
}

size_t PtrVector_Reserve(PtrVector* vec, size_t new_size) {
    assert(vec != NULL);
    if (vec->array_capacity < new_size) {
        void** ptr = realloc(vec->array_ptr, new_size * sizeof(void*));
        if (ptr != NULL) {
            vec->array_ptr = ptr;
            vec->array_capacity = new_size;
        }
    }
    return vec->array_capacity;
}

void PtrVector_Clear(PtrVector* vec, PtrVectorFreeFunc free_func) {
    assert(vec != NULL);

    if (free_func != NULL) {
        for (int i = 0; i < vec->array_num; ++i) {
            if (vec->array_ptr[i] != NULL)
                free_func(vec->array_ptr[i]);
        }
    }

    vec->array_num = 0;
}

/**
 * 在添加成员之后检查空间是否充足，如果不充足则重新分配空间
 * \param vec Vector对象
 * \return bool
 *  > true 检查正常
 *  > false 异常不能插入新成员
 */
static bool _PreAddItem(PtrVector* vec) {
    if (vec->array_num == vec->array_capacity) {
        size_t new_size = (vec->array_capacity * 3 / 2) + 1;
        void** ptr = realloc(vec->array_ptr, new_size * sizeof(void*));
        if (ptr != NULL) {
            vec->array_ptr = ptr;
            vec->array_capacity = new_size;
        } else {
            return false;
        }
    }
    return true;
}

bool PtrVector_PushBack(PtrVector* vec, void* item) {
    assert(vec != NULL);
    if (!_PreAddItem(vec))
        return false;

    vec->array_ptr[vec->array_num] = item;
    ++ vec->array_num;
    return true;
}

void* PtrVector_PopBack(PtrVector* vec) {
    assert(vec != NULL);
    if (vec->array_num > 0) {
        void* ptr = vec->array_ptr[vec->array_num - 1];
        -- vec->array_num;
        return ptr;
    }
    return NULL;
}

bool PtrVector_InsertAt(PtrVector* vec, void* item, int pos) {
    assert(vec != NULL);
    if (!_PreAddItem(vec))
        return false;

    for (int i = vec->array_num - 1; i >= pos; --i)
        vec->array_ptr[i+1] = vec->array_ptr[i];
    vec->array_ptr[pos] = item;
    ++ vec->array_num;

    return true;
}

void* PtrVector_RemoveAt(PtrVector* vec, int pos) {
    assert(vec != NULL);
    if (pos < 0 || pos >= vec->array_num)
        return NULL;

    void *item = vec->array_ptr[pos];
    for (int i = pos; i < vec->array_num - 1; ++i)
        vec->array_ptr[i] = vec->array_ptr[i+1];
    --vec->array_num;

    return item;
}

void* PtrVector_ReplaceAt(PtrVector* vec, int pos, void* new_item) {
    assert(vec != NULL);
    if (pos < 0 || pos >= vec->array_num)
        return NULL;

    void* ret = vec->array_ptr[pos];
    vec->array_ptr[pos] = new_item;

    return ret;
}

void* PtrVector_GetAt(PtrVector* vec, int pos) {
    assert(vec != NULL && pos >= 0);
    if (pos < vec->array_num) {
        return vec->array_ptr[pos];
    }
    return NULL;
}

int PtrVector_CountIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data) {
    assert(vec != NULL);
    if (cond_func == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond_func(item, cond_data))
            ++ count;
    }
    return count;
}

int  PtrVector_Find(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data, int start_pos) {
    assert(vec != NULL);
    if (cond_func == NULL || start_pos < 0 || start_pos >= vec->array_num)
        return -1;

    for (int i = start_pos; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond_func(item, cond_data))
            return i;
    }

    return -1;
}

void PtrVector_Foreach(PtrVector* vec, PtrVectorHandleFunc handle_func, void* handle_data) {
    assert(vec != NULL);
    if (handle_func == NULL)
        return;

    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        handle_func(item, handle_data);
    }
}

int  PtrVector_ForeachIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data,
                         PtrVectorHandleFunc handle_func, void* handle_data) {
    assert(vec != NULL);
    if (cond_func == NULL || handle_func == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond_func(item, cond_data)) {
            handle_func(item, handle_data);
            ++ count;
        }
    }

    return count;
}

PtrVector* PtrVector_Filter(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data) {
    assert(vec != NULL && cond_func != NULL);

    PtrVector* new_vec = PtrVector_Create(0);
    if (new_vec != NULL) {
        for (int i = 0; i < vec->array_num; ++i) {
            void *item = vec->array_ptr[i];
            if (cond_func(item, cond_data))
                PtrVector_PushBack(new_vec, item);
        }
    }

    return new_vec;
}

int PtrVector_RemoveIf(PtrVector *vec, PtrVectorCondFunc cond_func, void* cond_data, PtrVectorFreeFunc free_func) {
    assert(vec != NULL && cond_func != NULL);
    int remove_count = 0;
    for (int i = 0; i < vec->array_num; ++i) {
        if (remove_count > 0)
            vec->array_ptr[i-remove_count] = vec->array_ptr[i];

        void *item = vec->array_ptr[i];
        if (cond_func(item, cond_data)) {
            if (free_func != NULL)
                free_func(item);
            ++remove_count;
        }
    }
    vec->array_num -= remove_count;

    return remove_count;
}

void PtrVector_Destory(PtrVector* vec, PtrVectorFreeFunc free_func) {
    assert(vec != NULL);

    if (free_func != NULL) {
        for (int i = 0; i < vec->array_num; ++i) {
            if (vec->array_ptr[i] != NULL)
                free_func(vec->array_ptr[i]);
        }
    }

    free(vec->array_ptr);
    free(vec);
}
