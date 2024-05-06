#include "PriorityQueue.h"

template<class TValue>
auto PriorityQueue<TValue>::Node::operator<=>(const Node& other) const
{
    return Priority <=> other.Priority;
}

template<class TValue>
bool PriorityQueue<TValue>::Node::operator==(const Node& other) const
{
    return Value == other.Value && Priority == other.Priority;
}

template<class TValue>
PriorityQueue<TValue>::PriorityQueue(pointer Arr, size_type ArrSize)
{
    for (size_type i = 0; i < ArrSize; ++i) {
        Node node{ Arr[i], i };
        Data.insert(node);
    }
}

template<class TValue>
PriorityQueue<TValue>::PriorityQueue(const PriorityQueue& other) : Data(other.Data) {}

template<class TValue>
PriorityQueue<TValue>& PriorityQueue<TValue>::operator=(const PriorityQueue& other)
{
    if (this != &other) { Data = other.Data; }
    return *this;
}

template<class TValue>
typename PriorityQueue<TValue>::size_type PriorityQueue<TValue>::size() const noexcept
{
    return Data.size();
}

template<class TValue>
bool PriorityQueue<TValue>::empty() const noexcept { return Data.empty(); }

template<class TValue>
void PriorityQueue<TValue>::clear() noexcept { Data.clear(); }

template<class TValue>
void PriorityQueue<TValue>::insert(const reference value, const size_type priority) noexcept
{
    Node node{ value, priority };
    Data.insert(node);
}

template<class TValue>
void PriorityQueue<TValue>::pop() noexcept
{
    Node node = Data.getMax();
    Data.remove(node);
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, PriorityQueue<TValue>& list) {
    for (const auto& node : list.Data) { os << node.Value << ' '; }
    return os;
}



