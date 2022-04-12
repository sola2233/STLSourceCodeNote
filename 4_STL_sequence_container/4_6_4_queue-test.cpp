// file: 4queue-test.cpp
// 测试用 list 作为 queue 的底层容器

#include <queue>
#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    queue<int, list<int>> iqueue;
    iqueue.push(1);
    iqueue.push(3);
    iqueue.push(5);
    iqueue.push(7);

    cout << iqueue.size() << endl;
    cout << iqueue.front() << endl;

    iqueue.pop();
    cout << iqueue.front() << endl;
    iqueue.pop();
    cout << iqueue.front() << endl;
    iqueue.pop();
    cout << iqueue.front() << endl;
    cout << iqueue.size() << endl;

    return 0;
}