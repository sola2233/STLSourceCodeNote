// filename: 4vector-test.cpp
// vector 使用测试程序

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 打印 size 和 capacity，参数必须是 reference
inline void printInfo(vector<int>& iv)
{
    cout << "size=" << iv.size() << " capacity=" << iv.capacity() << endl;
}

// 打印 vector 元素，参数必须是 reference
void printVector(vector<int>& iv)
{
    for (int i = 0; i < iv.size(); i++)
    {
        cout << iv[i] << " ";
    }
    cout << endl;
}

int main()
{
    int i;
    // 构建一个包含两个 9 的vector
    vector<int> iv(2, 9);
    printInfo(iv);

    // 尾部插入 4 个元素
    for (i = 1; i < 5; i++)
    {
        iv.push_back(i);
        printInfo(iv);
    }
    printVector(iv);

    // 尾部插入 1 个元素
    iv.push_back(i);
    printInfo(iv);
    printVector(iv);

    // 删除尾部元素
    iv.pop_back();
    iv.pop_back();
    printInfo(iv);

    iv.pop_back();
    printInfo(iv);

    // 查找元素 1，并且删除
    vector<int>::iterator ivite = find(iv.begin(), iv.end(), 1);
    if (ivite != iv.end())
        iv.erase(ivite);
    printInfo(iv);
    printVector(iv);

    // 在 2 的前面插入 3 个 7
    ivite = find(iv.begin(), iv.end(), 2);
    if (ivite != iv.end())
        iv.insert(ivite, 3, 7);
    printInfo(iv);
    printVector(iv);

    iv.clear();
    printInfo(iv);
}