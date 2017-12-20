/**
 * File: str_vector.h
 *
 * 基于PtrVector进行封装，使用易用于字符串的存储
 *
 * 注意: 与PtrVector不同的是StrVector会管理成员的内存申请与释放
 *
 * Change Logs:
 * Date         Author      Notes
 * 2017-12-20   Sid lee     Create
 */
#ifndef STRING_VECTOR_H_20171220
#define STRING_VECTOR_H_20171220

#include "ptr_vector.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef PtrVector StrVector;

#define StrVector_Create    PtrVector_Create
#define StrVector_Size      PtrVector_Size
#define StrVector_Capacity  PtrVector_Capacity
#define StrVector_Reserve   PtrVector_Reserve
#define StrVector_CountIf   PtrVector_CountIf
#define StrVector_Find      PtrVector_Find
#define StrVector_Foreach   PtrVector_Foreach
#define StrVector_ForeachIf PtrVector_ForeachIf

//! 字中是否相箱条件函数
bool StrVector_CondFunc_StringEqual(void *item, void *arg);

int  StrVector_CountIfEqual(StrVector *vec, const char *str);
bool StrVector_IsExist(StrVector *vec, const char *str);

char* StrVector_GetAt(StrVector *vec, int pos);

int  StrVector_ForeachIfEqual(StrVector *vec, const char *str, PtrVectorHandleFunc handle_func, void* handle_data);

bool StrVector_PushBack(StrVector *vec, const char *str);
bool StrVector_PushBackIfNotExist(StrVector *vec, const char *str);

void StrVector_RemoveAt(StrVector *vec, int pos);
int  StrVector_RemoveIf(StrVector *vec, PtrVectorCondFunc cond_func, void* cond_data);

void StrVector_Clear(StrVector *vec);
void StrVector_Destory(StrVector *vec);

#ifdef __cplusplus
}
#endif

#endif //STRING_VECTOR_H_20171220
