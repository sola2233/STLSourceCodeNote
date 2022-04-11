# 序列式容器

## 4.2 vector

**vector 的迭代器**：vector 维护的是一个连续线性空间，所以 vector 的迭代器就是普通指针，不论元素型别是什么，且 vector 提供的是 Random Access Iterator。

vector 内部以三个迭代器来操作容器内的元素，如下所示：
```cpp
template<class T, class Alloc = alloc>
class vector {
protected:
  iterator start;           // 表示目前使用空间的头
  iterator finish;          // 表示目前使用空间的尾
  iterator end_of_storage;  // 表示目前可用空间的尾
};
```

[4_2_5_vector-test.cpp](4_2_5_vector-test.cpp)：vector 容器操作

[4_2_2_stl_vector.h](4_2_2_stl_vector.h)：SGI STL 的 vector 源代码，重点关注注释的部分，包括：
- push_back 函数，内部调用了 inset_aux 函数
- pop_back 函数
- erase 函数
- clear 函数
- insert 函数，代码比较重要，STL 的插入操作标准规范是插入的新节点位于插入点（迭代器，即插入位置）前方

> 注意事项：对 vector 的任何操作，一旦引起空间重新配置，指向原 vector 的所有迭代器就都失效了，因为 vector 的迭代器就是普通指针，空间重新配置后，原位置 vector 会被释放掉。

## 4.3 list

list 的节点结构如下：
```cpp
template<class T>
struct __list_node {
    // 型别其实可以为 __list_node<T>*
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
};
```

对于 vector，其迭代器就是指针，所以 vector 是 Random Access Iterator，而 list 并不是，所以需要设计迭代器结构，实现递增、递减等操作，实现一个 Bidirectional Iterator，具体实现见 stl_list.h。

> 注意事项：插入操作（insert）和接合操作（splice）都不会造成原有的 list 迭代器失效，甚至 list 元素删除操作也只有“指向被删除元素”的迭代器失效。

list 的结构不仅是一个双向链表，还是一个环形双向链表，只需要一个指向尾端空白节点的 node 指针就可以表示整个环状链表。

[4_3_5_list-test.cpp](4_3_5_list-test.cpp)：测试 list 容器操作

[4_3_2_stl_list.h](4_3_2_stl_list.h)：SGI STL 的 list 源代码，重点关注注释的部分，包括：
- 迭代器的设计
- list 的构造与内存管理
- list 的元素操作：push_back、push_front、erase、pop_front、pop_back、clear、remove、unique、splice、merge、reverse、sort
- 对于 sort 函数，这是 merge sort 的迭代实现，内部调用了 splice（内部调用了 transfer 迁移操作函数）接合函数和 merge 合并函数

[4_3_6_merge_sort.cpp](4_3_6_merge_sort.cpp)：迭代版归并排序，参考 sgi stl stl_list.h 里的 list 内置 sort

> 注意事项：merge 合并操作合并两个升序排序的链表，链表一定要已经排好序。