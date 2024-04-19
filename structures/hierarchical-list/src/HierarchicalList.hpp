#include "HierarchicalList.h"

template<class TValue>
HierarchicalList<TValue>::Node::Node(const reference Value, spNode Next, spNode Down)
{
}


template<class TValue>
HierarchicalList<TValue>::Iterator::Iterator(const iterator& it)
{
}

template<class TValue>
HierarchicalList<TValue>::Iterator::Iterator(HierarchicalList& list, spNode node)
{
}

template<class TValue>
typename HierarchicalList<TValue>::Iterator& HierarchicalList<TValue>::Iterator::operator=(const Iterator& other)
{
    return *this;
}


template<class TValue>
HierarchicalList<TValue>::Iterator::operator bool()
{
}


template<class TValue>
auto HierarchicalList<TValue>::Iterator::operator<=>(const iterator& other) const
{
    return;
}

template<class TValue>
bool HierarchicalList<TValue>::Iterator::operator==(const iterator& other) const
{
    return false;
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator++() const
{
    return iterator();
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator--() const
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::Iterator::operator++(int) const
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::Iterator::operator--(int) const
{
    return iterator();
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator+=(size_type n) const
{
    return iterator();
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator-=(size_type n) const
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::reference HierarchicalList<TValue>::Iterator::operator*()
{
    return reference();
}

template<class TValue>
HierarchicalList<TValue>::const_reference HierarchicalList<TValue>::Iterator::operator*() const
{
    return const_reference();
}

template<class TValue>
HierarchicalList<TValue>::HierarchicalList(pointer Arr, size_type ArrSize)
{
}

template<class TValue>
HierarchicalList<TValue>::HierarchicalList(const HierarchicalList& other)
{
}

template<class TValue>
HierarchicalList<TValue>& HierarchicalList<TValue>::operator=(const HierarchicalList& other)
{
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::begin() const
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::end() const
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::find(const reference value) const noexcept
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::size_type HierarchicalList<TValue>::size() const noexcept
{
    return size_type();
}

template<class TValue>
bool HierarchicalList<TValue>::empty() const noexcept
{
    return false;
}

template<class TValue>
void HierarchicalList<TValue>::clear() const noexcept
{
}

template<class TValue>
void HierarchicalList<TValue>::insert(const reference value) noexcept
{
}

template<class TValue>
void HierarchicalList<TValue>::remove(const reference value) noexcept
{
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, HierarchicalList<TValue>& list) {
    return os;
}

