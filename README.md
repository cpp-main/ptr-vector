[[中文]](README_CN.md)

# ptr\_vector

PtrVector是一个用C语言实现的简单指针容器，模仿C++的std::vector。  
使用它可以轻松解决C语言中没有容器支持，不易管理对象的痛点。

PtrVector容器对象主要有以下接口：

## 1. 创建、复制、筛选、销毁
```
PtrVector* PtrVector_Create(int reserved_size);
PtrVector* PtrVector_Clone(const PtrVector* ptr);
PtrVector* PtrVector_Filter(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);
void PtrVector_Destory(PtrVector* vec, PtrVectorFreeFunc free_func);
```

## 2. 获取容器成员个数、容量、预留容量
```
size_t PtrVector_Size(const PtrVector* vec);
size_t PtrVector_Capacity(const PtrVector* vec);
size_t PrtVector_Reserve(PtrVector* vec, size_t new_size);
```

## 3. 清空、追加、弹出、插入、删除、替换、获取
```
void PtrVector_Clear(PtrVector* vec, PtrVectorFreeFunc free_func);
bool PtrVector_PushBack(PtrVector* vec, void* item);
void* PtrVector_PopBack(PtrVector* vec);
bool PtrVector_InsertAt(PtrVector* vec, void* item, int pos);
void* PtrVector_RemoveAt(PtrVector* vec, int pos);
void* PtrVector_ReplaceAt(PtrVector* vec, int pos, void* new_item);
void* PtrVector_GetAt(PtrVector* vec, int pos);
```

## 4. 查找、统计、遍历、条件遍历、条件删除
```
int PtrVector_CountIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);
int PtrVector_Find(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data, int start_pos);
void PtrVector_Foreach(PtrVector* vec, PtrVectorHandleFunc handle_func, void* handle_data);
int PtrVector_ForeachIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data,
                        PtrVectorHandleFunc handle_func, void* handle_data);
int PtrVector_RemoveIf(PtrVector *vec, PtrVectorCondFunc cond_func, void* cond_data,
                       PtrVectorFreeFunc free_func);
```

欢迎大家使用！

#问题反馈
Email: hevake\_lcj@126.com  
QQ: 527020730  
微信: hevake\_lee
