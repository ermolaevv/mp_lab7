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
HierarchicalList<TValue>::HierarchicalList(pointer Arr, size_type ArrSize) : length(0), Start(nullptr), End()
{
    if (Arr) {
        for (size_type i = 0; i < ArrSize; ++i) {
            insert(Arr[i]);
        }
    }
}



template<class TValue>
HierarchicalList<TValue>::HierarchicalList(const HierarchicalList& other) : length(0), Start(nullptr), End()
{
    for (iterator it = other.begin(); it != other.end(); ++it) {
        insert(*it);
    }
}



template<class TValue>
HierarchicalList<TValue>& HierarchicalList<TValue>::operator=(const HierarchicalList& other)
{
    if (this != &other) {
         clear();
         for (iterator it = other.begin(); it != other.end(); ++it) { insert(*it); }
    }
    return *this;
}

template<class TValue>
typename HierarchicalList<TValue>::iterator HierarchicalList<TValue>::begin() const {
    // хз, делал исходя из подхода как в списке с пропусками
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), Start);
}

template<class TValue>
typename HierarchicalList<TValue>::iterator HierarchicalList<TValue>::end() const {
    // аналогично begin
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), nullptr);
}



template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::find(const reference value) const noexcept
{
    // не уверен
    spNode current = Start;
    while (current != nullptr) {
        if (current->Value == value) {
            return Iterator(*const_cast<HierarchicalList<TValue>*>(this), current);
        }
        current = current->Next.lock();
    }
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), nullptr);  
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
void HierarchicalList<TValue>::clear() noexcept
{
    Start.reset();
    End.reset();
    length = 0;
}

template<class TValue>
void HierarchicalList<TValue>::insert(const reference value) noexcept
{
    // в начало (МОЖНО И ПО ДРУГОМУ)
    spNode newNode = std::make_shared<Node>(value);
    if (!Start) {
        Start = newNode;
        End = Start;
    }
    else {
        newNode->Next = Start;  
        Start = newNode;
    }
    ++length;
}

template<class TValue>
void HierarchicalList<TValue>::insertAtDepth(const reference value, spNode parent) noexcept
{
    // НЕ УВЕРЕНННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННННН
    spNode newNode = std::make_shared<Node>(value);
    if (!parent) {  insert(value); }
    else {
        spNode child = parent->Down.lock(); 
        if (!child) { parent->Down = newNode; }
        else {
            while (child->Next.lock()) { child = child->Next.lock(); }
            child->Next = newNode; 
        }
    }
    ++length;
}

template<class TValue>
void HierarchicalList<TValue>::remove(const reference value) noexcept
{
    // не понимаю где ошибка
    spNode current = Start;
    spNode previous = nullptr;

    while (current != nullptr) {
        if (current->Value == value) {
            
            if (!previous) {
                Start = current->Next.lock();  
            }
            else {
                previous->Next = current->Next;  
            }
            --length;  
            return;  
        }
        previous = current;
        current = current->Next.lock();
    }
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, HierarchicalList<TValue>& list) {
    return os;
}

