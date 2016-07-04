#include <stdio.h>
#include <stdbool.h>
#include "ptr_vector.h"

void print_num(void *p) {
    printf("%c,", *(char*)p);
}

bool cond(void *p) {
    char v = *(char*)p;
    return (v > 'e');
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
    PtrVector_Foreach(vec, print_num);
    puts("=======");
    PtrVector_PopBack(vec);  //a, d, b,
    PtrVector_PushBack(vec, &e);  //a, d, b, e,
    PtrVector_PushBack(vec, &f);  //a, d, b, e, f,
    PtrVector_RemoveAt(vec, 2);  //a, d, e, f,
    PtrVector_Foreach(vec, print_num);
    puts("=======");
    PtrVector_InsertAt(vec, &f, 1);  //a, f, d, e, f,
    PtrVector_InsertAt(vec, &g, 0);  //g, a, f, d, e, f,
    PtrVector_PushBack(vec, &h);  //g, a, f, d, e, f, h
    PtrVector_Foreach(vec, print_num);
    puts("=======");
    PtrVector_ForeachIf(vec, cond, print_num); //g, f, f, h
    puts("=======");
    ptr_vector* new_vec = PtrVector_Filter(vec, cond);
    PtrVector_Foreach(new_vec, print_num); //g, f, f, h
    puts("=======");
    int count = PtrVector_CountIf(vec, cond);
    printf("count:%d\n", count);  //4
    puts("=======");
    ptr_vector* dup_vec = PtrVector_Dup(vec); //g, a, f, d, e, f, h
    PtrVector_Foreach(dup_vec, print_num);
    puts("=======");
    PtrVector_Destory(new_vec);
    PtrVector_Destory(vec);
}
