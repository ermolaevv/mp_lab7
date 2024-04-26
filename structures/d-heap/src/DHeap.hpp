#include "DHeap.h"
template<class TValue>
DHeap<TValue>::DHeap(size_type DescendantCount, pointer Arr, size_type ArrSize) :
    DescendantCount(DescendantCount),
    Data(Arr, Arr + ArrSize)
{
    for (size_type i = Data.size() / DescendantCount; i > 0; --i) { diving(i - 1); }
}

template<class TValue>
DHeap<TValue>::DHeap(const DHeap& other): DescendantCount(other.DescendantCount), Data(other.Data) {}

template<class TValue>
DHeap<TValue>& DHeap<TValue>::operator=(const DHeap& other)
{
    if (this != &other) {
        DescendantCount = other.DescendantCount;
        Data = other.Data;
    }
    return *this;
}

template<class TValue>
std::vector<typename DHeap<TValue>::value_type> DHeap<TValue>::toSortedVector() const noexcept
{
    DHeap<TValue> copy(*this);
    std::vector<value_type> sortedVector;
    while (!copy.empty()) {
        sortedVector.push_back(copy.getMax());
        int value = 0;
        copy.remove(value);
    }
    return sortedVector;
}

template<class TValue>
const typename DHeap<TValue>::value_type& DHeap<TValue>::getMax() const noexcept { return Data[0]; }


template<class TValue>
DHeap<TValue>::iterator DHeap<TValue>::begin() const { return Data.begin(); }

template<class TValue>
DHeap<TValue>::iterator DHeap<TValue>::end() const { return Data.end(); }

template<class TValue>
DHeap<TValue>::const_iterator DHeap<TValue>::find(const reference value) const noexcept
{
    return std::find(Data.begin(), Data.end(), value);
}

template<class TValue>
DHeap<TValue>::size_type DHeap<TValue>::size() const noexcept { return Data.size(); }

template<class TValue>
bool DHeap<TValue>::empty() const noexcept { return Data.empty(); }

template<class TValue>
void DHeap<TValue>::clear() noexcept { Data.clear(); }

template<class TValue>
void DHeap<TValue>::insert(const reference value) noexcept
{
    Data.push_back(value);
    surfacing(Data.size() - 1);
}

template<class TValue>
void DHeap<TValue>::remove(const reference value) noexcept
{
    //
}

template<class TValue>
void DHeap<TValue>::diving(size_type index)
{
    size_type maxChildIndex = index * DescendantCount + 1;
    while (maxChildIndex < Data.size()) {
        size_type lastChildIndex = std::min(maxChildIndex + DescendantCount - 1, Data.size() - 1);
        for (size_type i = maxChildIndex + 1; i <= lastChildIndex; ++i) {
            if (Data[i] > Data[maxChildIndex]) { maxChildIndex = i; }
        }
        if (Data[index] >= Data[maxChildIndex]) { break; }
        std::swap(Data[index], Data[maxChildIndex]);
        index = maxChildIndex;
        maxChildIndex = index * DescendantCount + 1;
    }
}

template<class TValue>
void DHeap<TValue>::surfacing(size_type index)
{
    size_type p = (index - 1) / DescendantCount;
    while (index > 0 && Data[index] > Data[p]) {
        std::swap(Data[index], Data[p]);
        index = p;
        p = (index - 1) / DescendantCount;
    }
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, DHeap<TValue>& list)
{
    for (const auto& value : list) { os << value << ' '; }
    return os;
}
