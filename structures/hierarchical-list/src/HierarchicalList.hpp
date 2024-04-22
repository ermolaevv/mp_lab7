#include "HierarchicalList.h"

template<class TValue>
HierarchicalList<TValue>::Node::Node(const reference Value, spNode Next, spNode Down):
    Value(Value),
    Next(Next),
    Down(Down)
{}

template<class TValue>
HierarchicalList<TValue>::Iterator::Iterator(const iterator& it):
    List(it.List),
    Node(it.Node)
{}

template<class TValue>
HierarchicalList<TValue>::Iterator::Iterator(HierarchicalList& list, spNode node):
    List(list),
    Node(node)
{}

template<class TValue>
typename HierarchicalList<TValue>::Iterator& HierarchicalList<TValue>::Iterator::operator=(const Iterator& other)
{
    if (this != &other) {
        List = other.List;
        Node = other.Node;
    }
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::Iterator::operator bool() { return Node != nullptr; }

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator++() 
{
    if (Node) { Node = Node->Next.lock(); }
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::Iterator::operator++(int) 
{
    Iterator temp = *this;
    if (Node) { Node = Node->Next.lock(); }
    return temp;
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator+=(size_type n)
{
    for (size_type i = 0; i < n; ++i) {
        if (Node) { Node = Node->Next.lock(); }
        else { break; }
    }
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::reference HierarchicalList<TValue>::Iterator::operator*()
{
    if (Node) { return Node->Value; }
    else { throw std::runtime_error("Attempt to dereference end iterator"); }
}


template<class TValue>
HierarchicalList<TValue>::HierarchicalList(pointer Arr, size_type ArrSize): length(ArrSize), Start(nullptr), End()
{
    if (ArrSize > 0) {
        Start = std::make_shared<Node>(Arr[0]);
        spNode currentNode = Start;
        for (size_type i = 1; i < ArrSize; ++i) {
            insertAfter(currentNode, Arr[i]);
            currentNode = currentNode->Next.lock();
        }
        End = currentNode;
    }
}

template<class TValue>
HierarchicalList<TValue>::HierarchicalList(const HierarchicalList& other): length(other.length), Start(nullptr), End()
{
    if (other.Start) {
        Start = std::make_shared<Node>(*other.Start);
        spNode currentNode = Start;
        spNode otherNode = other.Start->Next.lock();
        while (otherNode) {
            currentNode->Next = std::make_shared<Node>(*otherNode);
            currentNode = currentNode->Next.lock();
            otherNode = otherNode->Next.lock();
        }
        End = currentNode;
    }
}

template<class TValue>
HierarchicalList<TValue>& HierarchicalList<TValue>::operator=(const HierarchicalList& other)
{
    if (this != &other) {

    }
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::begin() const
{
    return Iterator(*this, Start);
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::end() const
{
    return Iterator(*this, nullptr);
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::find(const reference value) const noexcept
{
    return iterator();
}

template<class TValue>
HierarchicalList<TValue>::size_type HierarchicalList<TValue>::size() const noexcept
{
    return length;
}

template<class TValue>
bool HierarchicalList<TValue>::empty() const noexcept
{
    return length == 0;
}

template<class TValue>
void HierarchicalList<TValue>::clear() const noexcept
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

