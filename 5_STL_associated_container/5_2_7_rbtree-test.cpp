// file: 5rbtree-test.cpp
// https://sandychn.github.io/2020/05/stl-rb_tree/
// 测试 stl rb-tree 的使用

#include <iostream>
#include <bits/stl_tree.h>  // 通常程序中不应该使用
using namespace std;

struct Node
{
    int first, second;
    Node(int _first, int _second) : first(_first), second(_second){};

    friend ostream &operator<<(ostream &outs, const Node &node)
    {
        outs << '{' << node.first << ',' << node.second << '}';
        return outs;
    }
};

// 返回 value 的 key 值
template <class T>
struct KeyOfValue
{
    // MUST return const int&, not int.
    // if return int, segmentation fault will occur.
    // I have spent much time because of this.
    const int &operator()(const T &obj) const
    {
        // key 和 value 相等，直接返回 value
        return obj;
    }
};

int main()
{
    _Rb_tree<int, int, KeyOfValue<int>, less<int>> itree;

    // 测试插入节点
    cout << itree.size() << endl;

    itree._M_insert_unique(10);
    itree._M_insert_unique(7);
    itree._M_insert_unique(8);

    itree._M_insert_unique(15);
    itree._M_insert_unique(5);
    itree._M_insert_unique(6);

    itree._M_insert_unique(11);

    itree._M_insert_unique(13);
    itree._M_insert_unique(12);

    cout << itree.size() << endl;

    // 打印所有节点的 value 和颜色，测试 operator++
    _Rb_tree<int, int, KeyOfValue<int>, less<int>>::iterator ite1 = itree.begin();
    _Rb_tree<int, int, KeyOfValue<int>, less<int>>::iterator ite2 = itree.end();
    for (; ite1 != ite2; ++ite1)
        cout << *ite1 << "(" << ite1._M_node->_M_color << ") ";
    cout << endl;

    return 0;
}