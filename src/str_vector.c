/**
 * File: str_vector.c
 *
 * Change Logs:
 * Date         Author      Notes
 * 2017-12-20   Sid lee     Create
 */

#include "str_vector.h"

#define __USE_BSD 
#include <string.h>

bool StrVector_CondFunc_StringEqual(void *item, void *arg) {
    const char *lhs_str = (const char*) item;
    const char *rhs_str = (const char*) arg;

    return 0 == strcmp(lhs_str, rhs_str);
}

int  StrVector_CountIfEqual(StrVector *vec, const char *str) {
    return PtrVector_CountIf(vec, StrVector_CondFunc_StringEqual, (void*)str);
}

bool StrVector_IsExist(StrVector *vec, const char *str) {
    int pos = StrVector_Find(vec, StrVector_CondFunc_StringEqual, (void*)str, 0);
    return pos != -1;
}

char* StrVector_GetAt(StrVector *vec, int pos) {
    return (char *)PtrVector_GetAt(vec, pos);
}

int  StrVector_ForeachIfEqual(StrVector *vec, const char *str,
                              PtrVectorHandleFunc handle_func, void* handle_data) {
    return PtrVector_ForeachIf(vec, StrVector_CondFunc_StringEqual, (void*)str, handle_func, handle_data);
}

bool StrVector_PushBack(StrVector *vec, const char *str) {
    return PtrVector_PushBack(vec, strdup(str));
}

bool StrVector_PushBackIfNotExist(StrVector *vec, const char *str) {
    if (!StrVector_IsExist(vec, str)) {
        return StrVector_PushBack(vec, str);
    }
    return false;
}

void StrVector_RemoveAt(StrVector *vec, int pos) {
    char *item_to_be_free = PtrVector_RemoveAt(vec, pos);
    if (item_to_be_free != NULL) {
        free(item_to_be_free);
    }
}

int StrVector_RemoveIf(StrVector *vec, PtrVectorCondFunc cond_func, void* cond_data) {
    return PtrVector_RemoveIf(vec, cond_func, cond_data, free);
}

void StrVector_Clear(StrVector *vec) {
    PtrVector_Clear(vec, free);
}

void StrVector_Destory(StrVector *vec) {
    PtrVector_Destory(vec, free);
}
