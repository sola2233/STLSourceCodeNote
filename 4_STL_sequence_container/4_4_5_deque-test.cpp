// filename: 4deque-test.cpp

#include <deque>
#include <iostream>
#include <algorithm>
using namespace std;

class alloc
{
};

int main()
{
    deque<int, allocator<int>> ideq(20, 9);
    cout << "size=" << ideq.size() << endl;     // size=20

    // 为每一个元素设定新值
    for (int i = 0; i < ideq.size(); ++i)
        ideq[i] = i;

    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;                               // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

    // 在尾端增加 3 个元素，其值为 0、1、2
    for (int i = 0; i < 3; ++i)
        ideq.push_back(i);

    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;                               // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 
    cout << "size=" << ideq.size() << endl;     // size=23

    // 在尾端增加 1 个元素，其值为 3
    ideq.push_back(3);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;                               // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3
    cout << "size=" << ideq.size() << endl;     // size=24

    // 在最前端增加 1 个元素，其值为 99
    ideq.push_front(99);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;                               // 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3
    cout << "size=" << ideq.size() << endl;     // size=25

    // 在最前端增加 2 个元素，其值为 98、97
    ideq.push_front(98);
    ideq.push_front(97);
    for (int i = 0; i < ideq.size(); ++i)
        cout << ideq[i] << ' ';
    cout << endl;                               // 97 98 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0 1 2 3
    cout << "size=" << ideq.size() << endl;     // size=27

    // 搜寻数值为 99 的元素，并打印出来
    deque<int, allocator<int>>::iterator itr;
    itr = find(ideq.begin(), ideq.end(), 99);
    cout << *itr << endl;                       // 99
    cout << *(itr._M_cur) << endl;              // 99

    return 0;
}