# 迭代器概念与traits编程技法

## 3.1 迭代器设计思维——STL关键所在

STL的中心思想：将数据容器和算法分开，最后再以一胶着剂将它们撮合在一起。

迭代器就是容器和算法之间的胶着剂。

[3_1_find.cpp](3_1_find.cpp)：只要给予不同的迭代器，find 便能够对不同的容器进行查找操作

## 3.2 迭代器是一种smart pointer

[3_2_autoptr.cpp](3_2_autoptr.cpp)：简化版的auto_ptr，迭代器的设计可以参考auto_ptr

[3_2_mylist.h](3_2_mylist.h)：实现了一个简单的 list，为了测试自己实现的迭代器

[3_2_mylist-iter.h](3_2_mylist-iter.h)：实现了一个 list 的迭代器，实际上 list 中的接口暴露了太多给迭代器

[3_2_algorithm.h](3_2_algorithm.h)：find 函数和 for_each 函数，下面代码测试迭代器用

[3_2_mylist-iter-test.cpp](3_2_mylist-iter-test.cpp)：测试迭代器和 list，因为 find 函数里的判断元素操作，需要重载 operator!= 函数

## 3.3 迭代器相应型别

迭代器的相应型别有五种，迭代器所指对象的型别就是其中之一，可以利用 function template 的参数推导（argument deducation）机制来实现。不过不是所有迭代器相应型别都可以利用 template 参数推导机制获得。

## 3.4 Traits编程技法——STL源代码门钥

template 参数推导机制只能推导参数，无法推导函数的返回值型别，所以，每个迭代器内部都要声明内嵌型别：

```cpp
template <typename T>
struct MyIter {
    typedef T value_type; // 内嵌型别声明
}
```

这样，当函数使用到迭代器时，就可以获取其类型：

```cpp
template <typename I>
typename I::value_type  // 这一整行都是返回值，加上 typename 是为了告诉编译器这是一个型别
func(I ite)
{
    return *ite;
}
```

但是，这里还有个问题，并非所有迭代器都是 class type，原生指针就无法定义内嵌型别，可以利用模板偏特化解决问题（template partial specialization）：
```cpp
template <typename T>
class C { };    // 这个泛化版本允许 T 为任何型别

template <typename T>
class C<T*> { }; // 这个特化版本仅适用于 T 为原生指针的情况
```

如下 class template 专门用来萃取迭代器的特性，value type 正是迭代器特性之一：
```cpp
template <class I>
struct iterator_traits {    // traits 意味特性
    // 如果迭代器 I 定义了字节的 value type，那么就可以萃取出来
    typedef typename I::value_type value_type;
}
```

所以，之前的 func 可以改成这样：
```cpp
template <typename I>
typename iterator_traits<I>::value_type  // 这一整行都是返回值，加上 typename 是为了告诉编译器这是一个型别
func(I ite)
{
    return *ite;
}
```

多了一层间接性的好处就是，traits 可以拥有特化版本，下面的偏特化版本中，迭代器就是个原生指针：
```cpp
template <typename T>
struct iterator_traits<T*> {    // 偏特化版，这里迭代器是一个原生指针
    typedef T value_type;
}
```

但是，针对指向常数对象的指针，会得到一个 const 对象，可以再设计一个特化版本，解决这个问题：
```cpp
template <typename T>
struct iterator_traits<const T*> {  // 偏特化版，当迭代器是一个 pointer-to-const 时
    typedef T value_type;           // 萃取出来的型别应该是 T，不是 const T
}
```

> 至此，不论是迭代器 MyIter，原生指针 int* 或 const int*，都可以通过 traits 取出正确的 value type。这是建立在每一个迭代器都遵守约定，以内嵌型别定义的方式定义出相应型别的基础上。

最常用到的迭代器相应型别有五种，再看看书上的两个偏特化版本：
```cpp
template<class I>
struct iterator_traits {
    // 迭代器型别标签，迭代器有五种类型，Input、Output、Forward、Bidirectional、Random Access，其中后三种都用了继承
    typedef typename I::iterator_category   iterator_category;
    // 迭代器所指对象的型别
    typedef typename I::value_type          value_type;
    // 两个迭代器之间的距离，也可以用来表示一个容器的最大容量
    typedef typename I::difference_type     difference_type;
    // 返回一个指针，指向迭代器所指之物
    typedef typename I::pointer             pointer;
    // 返回迭代器所指对象的内容，如果可改变，返回左值 reference，否则返回一个右值 const reference
    typedef typename I::reference           reference;
}
```

书上举了 advance() 函数（迭代器递增）的例子，利用模板函数重载，对不同类型的迭代器（iterator_category）调用不同的 __advance() 函数，五种迭代器类型如下，分别作为 __advance() 的参数传递（并不使用，纯粹用来激活重载机制）：
```cpp
// 五个作为标记用的型别（tag types）
struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag { };
struct random_access_iterator_tag : public bidirectional_iterator_tag { };
```

[3_4_tag-test.cpp](3_4_tag-test.cpp)：通过继承，不必再写“单纯只做传递调用”的函数，例如 forward_iterator_tag 继承自 input_iterator_tag，则传递 forward_iterator_tag 对象会自动调用 input_iterator_tag 版本的函数

## 3.6 iterator源代码完整重列

[3_6_stl_iterator.h](3_6_stl_iterator.h)：SGI STL <stl_iterator.h> 头文件，包括
- 五种迭代器类型
- 迭代器的基类 iterator，防止自行设计迭代器时遗漏相应型别
- 特性萃取类 iterator_traits 和两个针对原生指针和 pointer-to-const 的特化版本
- distance 和 advance 等函数

## 3.7 SGI STL的私房菜：__type_traits

iterator_traits 负责萃取迭代器的特性，__type_traits 则负责萃取型别（type）的特性。此处的型别特性是指：这个型别是否具备 non-trivial defalt ctor、non-trival copy ctor、non-trival assignment operator、non-trival dtor。如果答案是否定的，就可以采取最有效率的措施。

[3_7_type_traits.h](3_7_type_traits.h)：针对不同的型别属性，在编译时期完成函数派送决定，通过 __type_traits 萃取特性，利用函数重载在编译时决定调用哪个函数