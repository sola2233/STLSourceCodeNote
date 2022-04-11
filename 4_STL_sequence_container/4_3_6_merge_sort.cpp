/** 
 * 迭代版归并排序，参考 sgi stl stl_list.h 里的 list 内置 sort
 * [参考了知乎评论区几个回答](https://www.zhihu.com/question/31478115)
 */
#include <list>
#include <vector>
#include <iostream>

using namespace std;

// 迭代版归并排序
list<int> MergeSort(list<int>& ll)
{
    // 以下判断，如果是空链表，或仅有一个元素，就不进行任何操作
    if (ll.empty() || ll.size() == 1)
        return ll;
    
    // 一些新的 list，作为中介数据存放区
    list<int> carry;
    // 64 个槽位，最多存放 2^63 大小的数据，完全够用
    vector<list<int>> counter(64);
    // 用表示最后一个存放数据的槽位后面那个空槽位的下标
    int fill = 0;
    // 当 ll 还有数据时
    while (!ll.empty())
    {
        // 每次从 ll 中取出一个节点放到 carry 中
        carry.push_back(*(ll.begin()));
        ll.pop_front();
        // 结束条件，遇到了下一个为空的槽位或前面的旧的空槽位
        int i = 0;
        while (i < fill && !counter[i].empty())
        {
            // merge 把两个有序链表合并为一个
            counter[i].merge(carry);
            // 交换到 carry 里，往后面槽位里的链表合并
            carry.swap(counter[i++]);
        }
        // 结束循环后再把 carry 里的数据转移到 counter 中
        // 如果是 i < fill 条件结束的，就放到 counter[fill] 中
        // 如果是 !counter[i].empty() 条件结束的，就放到前面旧的空槽位中，等待下次合并
        carry.swap(counter[i]);
        // 如果是 i < fill 条件结束的，此时 counter[fill] 中已经存放了数据
        // 所以 fill 要自增，找到下一个空槽位
        if (i == fill)
            ++fill;
    }

    // ll 中所有数据都取出后，合并 counter 所有槽位的链表
    for (int i = 1; i < fill; ++i)
        counter[i].merge(counter[i - 1]);
    
    return counter[fill - 1];
}

int main()
{
    list<int> ll = {2, 9, 1, 8, 7, 4, 6, 5, 3};
    for (auto i : ll)
        cout << i << " ";
    cout << endl;

    list<int> res = MergeSort(ll);
    for (auto i : res)
        cout << i << " ";
    cout << endl;

    return 0;
}