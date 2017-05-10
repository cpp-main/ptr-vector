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
 *
 * 2016-07-22   Sid lee
 * 1. 新增3个常用函数Capacity, Reserve, Clear
 *
 * 2016-07-26   Sid lee
 * 1. 修改Destory()，添加指针元素释放函数，方便使用。
 */
#ifndef PTR_VERTOR_H_20160704
#define PTR_VERTOR_H_20160704

#include <stdlib.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

//! 容器对象申明
struct PtrVector;
typedef struct PtrVector PtrVector;

//! 条件判断函数指针
typedef bool (PtrVectorCondFunc)(void *item, void *cond_data);
//! 元素处理函数指针
typedef void (PtrVectorHandleFunc)(void *item, void *handle_data);
//! 元素释放函数指针
typedef void (PtrVectorFreeFunc)(void *item);

///////////////////////////////////////////////////////////////////////////////
//  Functions
///////////////////////////////////////////////////////////////////////////////

/**
 * 创建PtrVector容器对象
 * \param reserved_size 预设大小
 * \return PtrVector 容器对象
 */
PtrVector* PtrVector_Create(size_t reserved_size);

//! 复制PtrVector容器对象
//! 注意：只clone容器本身，不对成员指针所指对象进行clone
PtrVector* PtrVector_Clone(const PtrVector* ptr);

//! 获取容器的元素个数
size_t PtrVector_Size(const PtrVector* vec);

//! 获取容器当前容量
size_t PtrVector_Capacity(const PtrVector* vec);

//! 预留空间大小，为防止频繁申请空间
size_t PtrVector_Reserve(PtrVector* vec, size_t new_size);

//! 清空容器
//! 如果free_func不为NULL，则会用free_func处理每一个成员，通常用free()
void PtrVector_Clear(PtrVector* vec, PtrVectorFreeFunc free_func);

//! 将容器尾部追加元素
bool PtrVector_PushBack(PtrVector* vec, void* item);

//! 从容器尾部弹出元素
void* PtrVector_PopBack(PtrVector* vec);

//! 插入一个新元素到容器pos位置
bool PtrVector_InsertAt(PtrVector* vec, void* item, int pos);

//! 移除容器pos位置的元素。如果成功，则返回该元素
void* PtrVector_RemoveAt(PtrVector* vec, int pos);

//! 替换容器pos位置的元素。如果成功，则返回替换前的元素
void* PtrVector_ReplaceAt(PtrVector* vec, int pos, void* new_item);

//! 获取容器pos位置的元素
void* PtrVector_GetAt(PtrVector* vec, int pos);

/**
 * 统计容器中满足cond条件的元素个数
 * \param vec
 * \param cond_func 条件函数指针
 * \param cond_data 条件附加参数指针
 * \return int 满足条件的元素个数
 */
int PtrVector_CountIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);

/**
 * 从容器中找出第一个符合cond函数判定条件元素的位置
 * \param vec
 * \param cond_func 判定函数指针
 * \param cond_data 条件附加参数指针
 * \param start_pos 搜索起始位置
 * \return int 元素的位置
 *  > -1 没有找到该元素
 */
int PtrVector_Find(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data, int start_pos);

/**
 * 对每个元素执行handle函数
 * \param vec
 * \param handle_func 处理函数指针
 * \param handle_data 处理函数附加参数指针
 */
void PtrVector_Foreach(PtrVector* vec, PtrVectorHandleFunc handle_func, void* handle_data);

/**
 * 对每个符合cond判定条件的元素执行handle处理
 * \param vec
 * \param cond_func 条件判定函数指针
 * \param cond_data 条件附加参数指针
 * \param handle_func 处理函数指针
 * \param handle_data 处理函数附加参数指针
 * \return int 被处理的元素个数
 */
int PtrVector_ForeachIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data,
                        PtrVectorHandleFunc handle_func, void* handle_data);

/**
 * 筛选出满足条件cond的元素，并将元素放置在新容器中并返回容器
 * \param vec
 * \param cond_func 条件判定函数指针
 * \param cond_data 条件附加参数指针
 * \return PtrVector* 新容器对象
 */
PtrVector* PtrVector_Filter(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);

/**
 * 移除出满足条件cond的元素，并释放元素
 * \param vec
 * \param cond_func 条件判定函数指针
 * \param cond_data 条件附加参数指针
 * \param free_func 释放函数指针
 *  > NULL，不释放其中的元素
 *  > 非NULL，释放容器中每个指针所指向的空间
 * \return int 被移除元素个数
 */
int PtrVector_RemoveIf(PtrVector *vec, PtrVectorCondFunc cond_func, void* cond_data, PtrVectorFreeFunc free_func);

/**
 * 销毁容器
 * \param vec
 * \param free_func 元素释放函数指针
 *  > NULL，不释放其中的元素
 *  > 非NULL，释放容器中每个指针所指向的空间
 */
void PtrVector_Destory(PtrVector* vec, PtrVectorFreeFunc free_func);

#ifdef __cplusplus
}
#endif

#endif //PTR_VERTOR_H_20160704
