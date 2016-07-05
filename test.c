#include <stdio.h>
#include <stdbool.h>
#include "ptr_vector.h"

void print(void *p, void *d) {
    (void)d;
    printf("%c,", *(char*)p);
}

bool cond(void *p, void *d) {
    return (*(char*)p > *(char*)d);
}

int main() {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    char e = 'e', f = 'f', g = 'g', h = 'h';

    puts("=======");
    ptr_vector* vec = PtrVector_Create(1);
    PtrVector_PushBack(vec, &a);
    PtrVector_PushBack(vec, &b);
    PtrVector_PushBack(vec, &c);
    PtrVector_InsertAt(vec, &d, 1);  //a, d, b, c
    PtrVector_Foreach(vec, print, NULL);
    puts("=======");
    PtrVector_PopBack(vec);  //a, d, b,
    PtrVector_PushBack(vec, &e);  //a, d, b, e,
    PtrVector_PushBack(vec, &f);  //a, d, b, e, f,
    PtrVector_RemoveAt(vec, 2);  //a, d, e, f,
    PtrVector_Foreach(vec, print, NULL);
    puts("=======");
    PtrVector_InsertAt(vec, &f, 1);  //a, f, d, e, f,
    PtrVector_InsertAt(vec, &g, 0);  //g, a, f, d, e, f,
    PtrVector_PushBack(vec, &h);  //g, a, f, d, e, f, h
    PtrVector_Foreach(vec, print, NULL);
    puts("=======");
    PtrVector_ForeachIf(vec, cond, &e, print, NULL); //g, f, f, h
    puts("=======");
    ptr_vector* new_vec = PtrVector_Filter(vec, cond, &e);
    PtrVector_Foreach(new_vec, print, NULL); //g, f, f, h
    puts("=======");
    int count = PtrVector_CountIf(vec, cond, &e);
    printf("count:%d\n", count);  //4
    puts("=======");
    ptr_vector* dup_vec = PtrVector_Dup(vec); //g, a, f, d, e, f, h
    PtrVector_Foreach(dup_vec, print, NULL);
    puts("=======");
    PtrVector_ForeachIf(vec, cond, &f, print, NULL); //g, h
    puts("=======");
    PtrVector_ReplaceAt(vec, 3, &c); //g, a, f, c, e, f, h
    PtrVector_Foreach(vec, print, NULL);
    puts("=======");
    PtrVector_Destory(new_vec);
    PtrVector_Destory(dup_vec);
    PtrVector_Destory(vec);
}
