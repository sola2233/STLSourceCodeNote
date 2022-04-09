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
   - 全局`construct()`函数实际上调用了`placement new`函数
   - 全局`destroy()`函数会根据元素型别做不同的处理，为了提高效率
3. [stl_uninitialized.h](2_3_1_stl_uninitialized.h)：定义了一些全局函数，用来填充（fill）或复制（copy）大块内存数据，也都隶属于STL标准规范。这些函数虽然不属于配置器的范畴，但是与对象初值的设置有关。对于容器的大规模元素处置设置很有帮助。这些函数对于效率都有面面俱到的考虑：
   - 最差情况下会调用`construct()`
   - 最佳情况下会使用C标准函数`memmove()`直接进行内存数据的移动

[stl内存池中使用union节省空间的问题](https://segmentfault.com/q/1010000006209284)

## 2.3 内存基本处理工具

[stl_uninitialized.h](2_3_1_stl_uninitialized.h)：包含了三个全局函数，作用都是在某个内存区块上构造元素。每个函数首先都会萃取迭代器first的value type，判断该型别是否为POD型别，然后令编译器调用合适的处理函数。对POD型别采用最有效率的初值填写收发，对 non-POD 型别采取最保险安全的做法
1. `uninitialized_copy()`
2. `uninitialized_fill()`
3. `uninitialized_fill_n()`

> POD（Plain Old Data），即标量型别或传统的 C struct 型别。POD 型别必然拥有 trivial ctor/dtor/copy/assignment 函数。