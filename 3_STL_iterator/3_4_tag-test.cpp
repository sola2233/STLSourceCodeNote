// file: 3tag-test.cpp
// 通过继承，消除 “单纯只做传递调用” 的函数
#include <iostream>
using namespace std;

struct B { };               // 类比 InputIterator
struct D1 : public B { };   // 类比 ForwardIterator
struct D2 : public D1 { };  // 类比 BidirectionalIterator

template <class I> 
void func(I& p, B) 
{
    cout << "B version" << endl;
}

template <class I> 
void func(I& p, D2) 
{
    cout << "D2 version" << endl;
}

int main() 
{
    int * p;
    func(p, B());   // 参数与参数完全吻合，输出：B version
    func(p, D1());  // 参数与参数不能完全吻合，因继承关系自动传递调用，输出：B version
    func(p, D2());  // 参数与参数完全吻合，输出：D2 version

    return 0;
}