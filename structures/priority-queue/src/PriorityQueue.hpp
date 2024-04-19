#include "PriorityQueue.h"

template<class TValue>
auto PriorityQueue<TValue>::Node::operator<=>(const Node& other) const
{
}

template<class TValue>
bool PriorityQueue<TValue>::Node::operator==(const Node& other) const
{
    return false;
}

template<class TValue>
PriorityQueue<TValue>::PriorityQueue(pointer Arr, size_type ArrSize)
{
}

template<class TValue>
PriorityQueue<TValue>::PriorityQueue(const PriorityQueue& other)
{
}

template<class TValue>
PriorityQueue<TValue>& PriorityQueue<TValue>::operator=(const PriorityQueue& other)
{
    return *this;
}

template<class TValue>
PriorityQueue<TValue>::size_type PriorityQueue<TValue>::size() const noexcept
{
    return size_type();
}

template<class TValue>
bool PriorityQueue<TValue>::empty() const noexcept
{
    return false;
}

template<class TValue>
void PriorityQueue<TValue>::clear() const noexcept
{
}

template<class TValue>
void PriorityQueue<TValue>::insert(const reference value, const size_type priority) noexcept
{
}

template<class TValue>
void PriorityQueue<TValue>::pop() noexcept
{
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, PriorityQueue<TValue>& list) {
    return os;
}

