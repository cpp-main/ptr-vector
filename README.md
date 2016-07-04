#ptr\_vector

PtrVector是一个用C语言实现的简单指针容器，模仿C++的std::vector
PtrVector对象主要有以下接口：

```
//! 创建、复制、筛选、销毁
ptr_vector* PtrVector_Create(int reserved_size);
ptr_vector* PtrVector_Dup(const ptr_vector* ptr);
ptr_vector* PtrVector_Filter(ptr_vector* vec, ptr_vector_cond_func cond);
void PtrVector_Destory(ptr_vector* vec);

//! 获取容器成员个数
size_t PtrVector_Size(const ptr_vector* vec);

//! 追加、弹出、插入、删除、获取
bool PtrVector_PushBack(ptr_vector* vec, void* item);
void* PtrVector_PopBack(ptr_vector* vec);
bool PtrVector_InsertAt(ptr_vector* vec, void* item, int pos);
void* PtrVector_RemoveAt(ptr_vector* vec, int pos);
void* PtrVector_GetAt(ptr_vector* vec, int pos);

//! 查找、统计、遍历、条件遍历
int  PtrVector_Find(ptr_vector* vec, ptr_vector_cond_func cond, int start_pos);
int PtrVector_CountIf(ptr_vector* vec, ptr_vector_cond_func cond);
void PtrVector_Foreach(ptr_vector* vec, ptr_vector_handle_func handle);
int PtrVector_ForeachIf(ptr_vector* vec, ptr_vector_cond_func cond, ptr_vector_handle_func handle);
```
