/*
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_CONSTRUCT_H
#define __SGI_STL_INTERNAL_CONSTRUCT_H

#include <new.h>

__STL_BEGIN_NAMESPACE

template <class T1, class T2>
inline void construct(T1 *p, const T2 &value)
{
	// placement new，调用 T1::T1(value)
	new (p) T1(value);
}

// destory 第一个版本，接受一个指针
template <class T>
inline void destroy(T *pointer)
{
	pointer->~T();
}

// dsetory 第二版本，接收两个迭代器。此函数设法找出元素的数值型别
// 进而利用 __type_traits<> 求取最适当措施
template <class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, value_type(first));
}

// 判断元素的数值型别(value type) 是否有 trivial destructor
template <class ForwardIterator, class T>
inline void __destroy(ForwardIterator first, ForwardIterator last, T *)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destroy_aux(first, last, trivial_destructor());
}


// 如果元素的数值型别(value type) 有 non-trivial destructor
template <class ForwardIterator>
inline void
__destroy_aux(ForwardIterator first, ForwardIterator last, __false_type)
{
	for (; first < last; ++first)
		destroy(&*first);
}

// 如果元素的数值型别(value type) 有 trivial destructor
template <class ForwardIterator>
inline void __destroy_aux(ForwardIterator, ForwardIterator, __true_type) {}

// 以下是 destroy 第二版针对迭代器为 char* 和 wchar_t* 的特化版
inline void destroy(char *, char *) {}
inline void destroy(wchar_t *, wchar_t *) {}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_CONSTRUCT_H */

// Local Variables:
// mode:C++
// End:
