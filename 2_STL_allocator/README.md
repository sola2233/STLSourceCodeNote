# 空间配置器(allocator)

## 2.1 空间配置器标准接口
[2_1_1jjalloc.h](2_1_1_jjalloc.h)：实现了一个简单的空间配置器，实现了书上 p46 页的接口，实际上内部分配内存时调用了全局的 operator new 函数，构造对象时调用了 placement new 函数

[2_1_1jjalloc.cpp](2_1_1_jjalloc.cpp)：测试`2_1_1jjalloc.h`中的空间配置器

[allocate函数中set_new_handle函数理解](https://blog.csdn.net/qq_14982047/article/details/50732568)

## 2.2 具备次配置力的SGI空间配置器

[2_2_1_defalloc.h](2_2_1_defalloc.h)：HP的 allocator 实现，SGI 中的空间配置器默认使用 alloc，并不使用这个 allocator，这里提供仅仅是为了回溯兼容

一般而言，C++内存配置操作 new 分为两个阶段，(同理，delete 也分为相反的两个步骤)：
1. 调用 ::operator new 配置内存
2. 调用构造函数构造对象

为了精密分工，STL allocator 将这两阶段区分开来：
1. 内存配置由 alloc::allocate() 负责，内存释放由 alloc::deallocate() 负责
2. 对象构造由 ::construct() 负责，对象析构由 ::destroy() 负责

STL 标准规定配置器定义于 [memory](2_2_2_memory) 中，SGI 的 memory 包含三个文件：
1. [stl_alloc.h](2_2_4_stl_alloc.h)：负责内存空间的配置与释放，里面定义了一、二级配置器，配置器名为 alloc
   - 当分配的内存小于 128kB 时，会直接调用第二级配置器，即 SGI 的 alloc
   - 当分配的内存大于 128kB 时，会调用第一级配置器，实际上就是 `malloc` 和 `free` 的封装
   - 无论 alloc 被定义为第一级配置器还是第二级配置器，SGI 还会为它再包装一个 `simple_alloc` 接口，使配置器能符合 STL 规范
2. [stl_construct.h](2_2_3_stl_construct.h)：负责对象内容的构造与析构，里面定义了全局函数 `construct()` 和 `destroy()`