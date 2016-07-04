/**
 * File: ptr_vector.h
 *
 * 指针Vector容器，类似C++的std::vector容器
 *
 * Change Logs:
 * Date         Author      Notes
 * 2016-04-07   Sid lee     Create
 */
#ifndef PTR_VERTOR_H_20160704
#define PTR_VERTOR_H_20160704

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//! 容器对象申明
struct ptr_vector;
typedef struct ptr_vector ptr_vector;

//! 条件判断函数指针
typedef bool (ptr_vector_cond_func)(void *);
//! 元素处理函数指针
typedef void (ptr_vector_handle_func)(void *);

///////////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////////

/** 
 * 创建ptr_vector容器对象
 * \param reserved_size 预设大小
 * \return ptr_vector 容器对象
 */
ptr_vector* PtrVector_Create(int reserved_size);

//! 复制ptr_vector容器对象
ptr_vector* PtrVector_Dup(const ptr_vector* ptr);

//! 获取容器的元素个数
size_t PtrVector_Size(const ptr_vector* vec);

//! 将容器尾部追加元素
bool PtrVector_PushBack(ptr_vector* vec, void* item);

//! 从容器尾部弹出元素
void* PtrVector_PopBack(ptr_vector* vec);

//! 插入一个新元素到容器pos位置
bool PtrVector_InsertAt(ptr_vector* vec, void* item, int pos);

//! 移除容器pos位置的元素。如果成功，则返回该元素
void* PtrVector_RemoveAt(ptr_vector* vec, int pos);

//! 获取容器pos位置的元素
void* PtrVector_GetAt(ptr_vector* vec, int pos);

/**
 * 统计容器中满足cond条件的元素个数
 * \param vec
 * \param cond 条件函数指针
 * \return int 满足条件的元素个数
 */
int PtrVector_CountIf(ptr_vector* vec, ptr_vector_cond_func cond);

/**
 * 从容器中找出第一个符合cond函数判定条件元素的位置
 * \param vec
 * \param cond 判定函数指针
 * \param start_pos 搜索起始位置
 * \return int 元素的位置
 *  > -1 没有找到该元素
 */
int  PtrVector_Find(ptr_vector* vec, ptr_vector_cond_func cond, int start_pos);

/**
 * 对每个元素执行handle函数
 * \param vec
 * \param handle 处理函数指针
 */
void PtrVector_Foreach(ptr_vector* vec, ptr_vector_handle_func handle);

/**
 * 对每个符合cond判定条件的元素执行handle处理
 * \param vec
 * \param cond 条件判定函数指针
 * \param handle 处理函数指针
 * \return int 被处理的元素个数
 */
int PtrVector_ForeachIf(ptr_vector* vec, ptr_vector_cond_func cond, ptr_vector_handle_func handle);

/**
 * 筛选出满足条件cond的元素，并将元素放置在新容器中并返回容器
 * \param vec
 * \param cond 条件判定函数指针
 * \return ptr_vector* 新容器对象
 */
ptr_vector* PtrVector_Filter(ptr_vector* vec, ptr_vector_cond_func cond);

/**
 * 销毁容器
 * \param vec
 * \note 不会释放元素指向的空间
 */
void PtrVector_Destory(ptr_vector* vec);

#ifdef __cplusplus
}
#endif

#endif //PTR_VERTOR_H_20160704
