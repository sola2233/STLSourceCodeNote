# 关联式容器

## 5.2 RB-tree（红黑树）

节点插入有四种情况，对于状况3和状况4，不直接旋转，而是先改变颜色，直到能转换成状况2或状况1，具体见代码。

RB-tree 的迭代器属于双向迭代器。迭代器的 increment 和 decrement 操作中，使用到了 RB-tree 结构中的特殊设计（header节点）。

header 设计：
- header 和 root 互为父节点
- header 是 RB-tree 的 end
- header 的 left 是最小 key 的迭代器
- header 的 right 是最大 key 的迭代器

**RB-tree 元素操作：**

RB-tree 的参数中需要一个 KeyOfValue 仿函数，它能根据 value 返回 key。

元素插入 insert_equal()，可重复

元素插入 insert_unique()，不可重复

真正的插入程序 __insert()

调整树形和颜色 __rb_tree_rebalance()

两个单旋操作：
1. __rb_tree_rotate_left
2. __rb_tree_rotate_right，参数为右旋点，对应 p210 的右旋点

[5_2_3_stl_tree.h](5_2_3_stl_tree.h)：红黑树节点、迭代器、红黑树结构的实现头文件，其中节点和迭代器都用了继承关系，在新版的头文件 "bits/stl_tree.h" 中迭代器不再使用继承

[5_2_7_rbtree-test.cpp](5_2_7_rbtree-test.cpp)：测试使用 stl 的红黑树结构，参考了网上代码