# 空间配置器(allocator)

`2_1_1jjalloc.h`：实现了一个简单的空间配置器，实现了书上 p46 页的接口，实际上内部分配内存时调用了全局的 operator new 函数，构造对象时调用了 placement new 函数

`2_1_1jjalloc.cpp`：测试`2_1_1jjalloc.h`中的空间配置器

`2_1_1_defalloc.h`：HP的 allocator 实现，SGI 中的空间配置器默认使用 alloc，并不使用这个 allocator，这里提供仅仅是为了回溯兼容

[allocate函数中set_new_handle函数理解](https://blog.csdn.net/qq_14982047/article/details/50732568)