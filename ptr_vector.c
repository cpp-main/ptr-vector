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

struct ptr_vector {
    void** array_ptr;   //! 指针数组指针
    size_t array_capacity;  //! 指针数组容量
    int    array_num;  //! 成员个数
};

///////////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////////

ptr_vector* PtrVector_Create(int reserved_size) {
    assert(reserved_size >= 0);
    ptr_vector* vec = calloc(1, sizeof(ptr_vector));
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

ptr_vector* PtrVector_Dup(const ptr_vector* src) {
    assert(src != NULL);
    ptr_vector* vec = calloc(1, sizeof(ptr_vector));
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

size_t PtrVector_Size(const ptr_vector* vec) {
    assert(vec != NULL);
    return vec->array_num;
}

/**
 * 在添加成员之后检查空间是否充足，如果不充足则重新分配空间
 * \param vec Vector对象
 * \return bool
 *  > true 检查正常
 *  > false 异常不能插入新成员
 */
static bool _PreAddItem(ptr_vector* vec) {
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

bool PtrVector_PushBack(ptr_vector* vec, void* item) {
    assert(vec != NULL);
    if (!_PreAddItem(vec))
        return false;

    vec->array_ptr[vec->array_num] = item;
    ++ vec->array_num;
    return true;
}

void* PtrVector_PopBack(ptr_vector* vec) {
    assert(vec != NULL);
    if (vec->array_num > 0) {
        void* ptr = vec->array_ptr[vec->array_num - 1];
        -- vec->array_num;
        return ptr;
    }
    return NULL;
}

bool PtrVector_InsertAt(ptr_vector* vec, void* item, int pos) {
    assert(vec != NULL);
    if (!_PreAddItem(vec))
        return false;
    
    for (int i = vec->array_num - 1; i >= pos; --i)
        vec->array_ptr[i+1] = vec->array_ptr[i];
    vec->array_ptr[pos] = item;
    ++ vec->array_num;

    return true;
}

void* PtrVector_RemoveAt(ptr_vector* vec, int pos) {
    assert(vec != NULL);
    if (pos < 0 || pos >= vec->array_num)
        return NULL;

    void *item = vec->array_ptr[pos];
    for (int i = pos; i < vec->array_num - 1; ++i)
        vec->array_ptr[i] = vec->array_ptr[i+1];
    --vec->array_num;

    return item;
}

void* PtrVector_GetAt(ptr_vector* vec, int pos) {
    assert(vec != NULL && pos >= 0);
    if (pos < vec->array_num) {
        return vec->array_ptr[pos];
    }
    return NULL;
}

int PtrVector_CountIf(ptr_vector* vec, ptr_vector_cond_func cond) {
    assert(vec != NULL);
    if (cond == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond(item))
            ++ count;
    }
    return count;
}

int  PtrVector_Find(ptr_vector* vec, ptr_vector_cond_func cond, int start_pos) {
    assert(vec != NULL);
    if (cond == NULL || start_pos < 0 || start_pos >= vec->array_num)
        return -1;

    for (int i = start_pos; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond(item))
            return i;
    }

    return -1;
}

void PtrVector_Foreach(ptr_vector* vec, ptr_vector_handle_func handle) {
    assert(vec != NULL);
    if (handle == NULL)
        return;

    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        handle(item);
    }
}

int  PtrVector_ForeachIf(ptr_vector* vec, ptr_vector_cond_func cond, ptr_vector_handle_func handle) {
    assert(vec != NULL);
    if (cond == NULL || handle == NULL)
        return 0;

    int count = 0;
    for (int i = 0; i < vec->array_num; ++i) {
        void *item = vec->array_ptr[i];
        if (cond(item)) {
            handle(item);
            ++ count;
        }
    }

    return count;
}

ptr_vector* PtrVector_Filter(ptr_vector* vec, ptr_vector_cond_func cond) {
    assert(vec != NULL && cond != NULL);

    ptr_vector* new_vec = PtrVector_Create(0);
    if (new_vec != NULL) {
        for (int i = 0; i < vec->array_num; ++i) {
            void *item = vec->array_ptr[i];
            if (cond(item))
                PtrVector_PushBack(new_vec, item);
        }
    }

    return new_vec;
}

void PtrVector_Destory(ptr_vector* vec) {
    assert(vec != NULL);
    free(vec->array_ptr);
    free(vec);
}
