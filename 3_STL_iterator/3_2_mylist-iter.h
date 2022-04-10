// file: 3mylist-iter.h
// 设计 list 的迭代器

// #include "3_2_mylist.h"

// Item 可以是单向链表节点或双向链表节点。
// 此处这个迭代器特定只为链表服务，因为其
// 独特的 operator++ 之故
template <class Item>
struct ListIter {
    Item *ptr; // 保持与容器的联系

    // default ctor
    ListIter(Item* p =0) : ptr(p) {}

    // 不必实现 copy ctor，因为编译器提供的默认行为已足够
    // 不必实现 operator=，因为编译器提供的默认行为已足够

    // 解引用 dereference
    Item& operator*() const {
        return *ptr;
    }

    // member access
    Item* operator->() const {
        return ptr;
    }

    // prefix increment, 返回对象
    ListIter& operator++() {
        ptr = ptr->next();
        return *this;
    }

    // postfix increment, 返回值（新对象）
    // int为占位符，提示编译器这是后自增
    ListIter operator++(int) {
        ListIter temp = *this;
        ++*this; // 调用前面的前自增
        return temp;
    }

    bool operator==(const ListIter& i) const {
        return ptr == i.ptr;
    }

    bool operator!=(const ListIter& i) const {
        return ptr != i.ptr;
    }
};