[[中文]](README_CN.md)

# ptr-vector

PtrVector is a simple pointer container implemented in C language, imitating C++'s std::vector.  
Using it can easily solve the pain point that there is no container support in C language and it is difficult to manage objects.

# Features

## 1. Create, Copy, Filter, Destroy
```
PtrVector* PtrVector_Create(int reserved_size);
PtrVector* PtrVector_Clone(const PtrVector* ptr);
PtrVector* PtrVector_Filter(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);
void PtrVector_Destory(PtrVector* vec, PtrVectorFreeFunc free_func);
```

## 2. Get the number of container members, capacity, reserved capacity
```
size_t PtrVector_Size(const PtrVector* vec);
size_t PtrVector_Capacity(const PtrVector* vec);
size_t PrtVector_Reserve(PtrVector* vec, size_t new_size);
```

## 3. Empty, Append, Pop, Insert, Delete, Replace, Get
```
void PtrVector_Clear(PtrVector* vec, PtrVectorFreeFunc free_func);
bool PtrVector_PushBack(PtrVector* vec, void* item);
void* PtrVector_PopBack(PtrVector* vec);
bool PtrVector_InsertAt(PtrVector* vec, void* item, int pos);
void* PtrVector_RemoveAt(PtrVector* vec, int pos);
void* PtrVector_ReplaceAt(PtrVector* vec, int pos, void* new_item);
void* PtrVector_GetAt(PtrVector* vec, int pos);
```

## 4. Search, statistics, traversal, conditional traversal, conditional deletion
```
int PtrVector_CountIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data);
int PtrVector_Find(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data, int start_pos);
void PtrVector_Foreach(PtrVector* vec, PtrVectorHandleFunc handle_func, void* handle_data);
int PtrVector_ForeachIf(PtrVector* vec, PtrVectorCondFunc cond_func, void* cond_data,
                        PtrVectorHandleFunc handle_func, void* handle_data);
int PtrVector_RemoveIf(PtrVector *vec, PtrVectorCondFunc cond_func, void* cond_data,
                       PtrVectorFreeFunc free_func);
```

# Feedback

- Issue: Any questions are welcome to communicate in issue
- WeChat: hevake\_lee
- QQ Group: 738084942 (cpp-tbox 技术交流)

# Encourage us

If this project makes your work easier and you leave work earlier, please give me more encouragement.
You can do these:  

- Light up three combos for it: Star, Watch, Fork;
- Recommend to colleagues and partners around you, and recommend to your readers in technical forums;
- Join the above QQ group, add me on WeChat to enter the WeChat group;
- Positive feedback on issues and suggestions;
- Participate in the development of the project and contribute your strength;
- Let me know which projects it is used in;

