/**
 * File: ptr_vector.h
 *
 * 指针Vector容器，类似C++的std::vector容器
 *
 * Change Logs:
 * Date         Author      Notes
 * 2016-07-04   Sid lee     Create
 * 2016-07-05   Sid lee
 * 1. 给Find, ForeachIf, CountIf, Filter方法的条件函数与处理函数添加data参数
 * 2. 新增Replace方法，避免使用RemoveAt, InsertAt造成大量移动操作
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
typedef bool (ptr_vector_cond_func)(void *item, void *cond_data);
//! 元素处理函数指针
typedef void (ptr_vector_handle_func)(void *item, void *handle_data);

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
ptr_vector* PtrVector_Clone(const ptr_vector* ptr);

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

//! 替换容器pos位置的元素。如果成功，则返回替换前的元素
void* PtrVector_ReplaceAt(ptr_vector* vec, int pos, void* new_item);

//! 获取容器pos位置的元素
void* PtrVector_GetAt(ptr_vector* vec, int pos);

/**
 * 统计容器中满足cond条件的元素个数
 * \param vec
 * \param cond_func 条件函数指针
 * \param cond_data 条件附加参数指针
 * \return int 满足条件的元素个数
 */
int PtrVector_CountIf(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data);

/**
 * 从容器中找出第一个符合cond函数判定条件元素的位置
 * \param vec
 * \param cond_func 判定函数指针
 * \param cond_data 条件附加参数指针
 * \param start_pos 搜索起始位置
 * \return int 元素的位置
 *  > -1 没有找到该元素
 */
int PtrVector_Find(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data, int start_pos);

/**
 * 对每个元素执行handle函数
 * \param vec
 * \param handle_func 处理函数指针
 * \param handle_data 处理函数附加参数指针
 */
void PtrVector_Foreach(ptr_vector* vec, ptr_vector_handle_func handle_func, void* handle_data);

/**
 * 对每个符合cond判定条件的元素执行handle处理
 * \param vec
 * \param cond_func 条件判定函数指针
 * \param cond_data 条件附加参数指针
 * \param handle_func 处理函数指针
 * \param handle_data 处理函数附加参数指针
 * \return int 被处理的元素个数
 */
int PtrVector_ForeachIf(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data,
                        ptr_vector_handle_func handle_func, void* handle_data);

/**
 * 筛选出满足条件cond的元素，并将元素放置在新容器中并返回容器
 * \param vec
 * \param cond_func 条件判定函数指针
 * \param cond_data 条件附加参数指针
 * \return ptr_vector* 新容器对象
 */
ptr_vector* PtrVector_Filter(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data);

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
