#ptr\_vector

PtrVector是一个用C语言实现的简单指针容器，模仿C++的std::vector。  
使用它可以轻松解决C语言中没有容器支持，不易管理对象的痛点。

PtrVector容器对象主要有以下接口：

##1. 创建、复制、筛选、销毁
```
ptr_vector* PtrVector_Create(int reserved_size);
ptr_vector* PtrVector_Dup(const ptr_vector* ptr);
ptr_vector* PtrVector_Filter(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data);
void PtrVector_Destory(ptr_vector* vec);
```

##2. 获取容器成员个数
```
size_t PtrVector_Size(const ptr_vector* vec);
```

##3. 追加、弹出、插入、删除、替换、获取
```
bool PtrVector_PushBack(ptr_vector* vec, void* item);
void* PtrVector_PopBack(ptr_vector* vec);
bool PtrVector_InsertAt(ptr_vector* vec, void* item, int pos);
void* PtrVector_RemoveAt(ptr_vector* vec, int pos);
void* PtrVector_ReplaceAt(ptr_vector* vec, int pos, void* new_item);
void* PtrVector_GetAt(ptr_vector* vec, int pos);
```

##4. 查找、统计、遍历、条件遍历
```
int PtrVector_CountIf(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data);
int PtrVector_Find(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data, int start_pos);
void PtrVector_Foreach(ptr_vector* vec, ptr_vector_handle_func handle_func, void* handle_data);
int PtrVector_ForeachIf(ptr_vector* vec, ptr_vector_cond_func cond_func, void* cond_data,
                        ptr_vector_handle_func handle_func, void* handle_data);
```

欢迎大家使用！

#问题反馈
Email: hevake\_lcj@126.com  
QQ: 527020730  
微信: hevake\_lcj
