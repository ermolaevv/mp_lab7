#include "DHeap.h"
template<class TValue>
DHeap<TValue>::DHeap(size_type DescendantCount, pointer Arr, size_type ArrSize)
{
}

template<class TValue>
DHeap<TValue>::DHeap(const DHeap& other)
{
}

template<class TValue>
DHeap<TValue>& DHeap<TValue>::operator=(const DHeap& other)
{
    return *this;
}

template<class TValue>
std::vector<typename DHeap<TValue>::value_type> DHeap<TValue>::toSortedVector() const noexcept
{
    return std::vector<value_type>();
}

template<class TValue>
DHeap<TValue>::reference DHeap<TValue>::getMax() const noexcept
{
    return reference();
}

template<class TValue>
DHeap<TValue>::iterator DHeap<TValue>::begin() const
{
    return iterator();
}

template<class TValue>
DHeap<TValue>::iterator DHeap<TValue>::end() const
{
    return iterator();
}

template<class TValue>
DHeap<TValue>::iterator DHeap<TValue>::find(const reference value) const noexcept
{
    return iterator();
}

template<class TValue>
DHeap<TValue>::size_type DHeap<TValue>::size() const noexcept
{
    return size_type();
}

template<class TValue>
bool DHeap<TValue>::empty() const noexcept
{
    return false;
}

template<class TValue>
void DHeap<TValue>::clear() const noexcept
{
}

template<class TValue>
void DHeap<TValue>::insert(const reference value) noexcept
{
}

template<class TValue>
void DHeap<TValue>::remove(const reference value) noexcept
{
}

template<class TValue>
void DHeap<TValue>::diving(size_type index)
{
}

template<class TValue>
void DHeap<TValue>::surfacing(size_type index)
{
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, DHeap<TValue>& list)
{
    return os;
}
