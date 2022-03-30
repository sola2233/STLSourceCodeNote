# 测试GCC在几个组态常量上的表现

测试`stl_config.h`中的各种组态

`1_9_1_config3.cpp`：测试编译器对模板静态成员初值的接受情况，gcc是接受的

`1_9_1_config5.cpp`：测试编译器对模板偏特化的支持情况，gcc支持

`1_9_1_config6.cpp`：不太明白

`1_9_1_config8.cpp`：测试模板类里面是不是还能有模板，gcc可以

`1_9_1_config10.cpp`：测试模板参数能否根据前一个模板参数而设定默认值，gcc可以

`1_9_1_config11.cpp`：测试类模板是否使用非类型模板参数

补充：
1. 当以类型 (type)作为模板参数的时候，代码中未决定的是类型；
2. 当以一般的数字(non-type)作为模板参数的时候，代码中待定的内容便是某些数值。使用者这种模板必须要显示指定数值，模板才能实例化。

`1_9_1_config-null-template-arguments.cpp`：bound friend templates，模板类的某个具现体与友元模板函数的某个具现体有一对一的关系，所以类模板中的友元模板函数要加 <>

`1_9_1_config-template-exp-special.cpp`：template <> 显示的模板特化(class template explicit specialization)，explicit specialization 必须加上 template<>

`1_9_2_config-temporary-object.cpp`：临时对象和仿函数搭配使用

`1_9_3_config-inclass-init.cpp`：静态常量可以类内初始化，静态成员变量必须类内声明，类外初始化，因为只有常量才能在类内拥有初始值

`1_9_4_config-operator-overloading.cpp`：自增(包括前置和后置)、自减、解引用操作符

`1_9_5_config-open-ended.cpp`：左闭右开区间的操作，实现了 find 函数和 for_each 函数

`1_9_6_functor.cpp`：简单的加法、减法函数调用重载，可以和匿名对象联合起来使用

`1_9_6_qsort.cpp`：C语言的函数指针，可以和仿函数比较一下