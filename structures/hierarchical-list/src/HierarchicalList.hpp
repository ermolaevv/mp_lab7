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
    if (Node) { Node = Node->Next; }
    return *this;
}

template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::Iterator::operator++(int) 
{
    Iterator temp = *this;
    if (Node) { Node = Node->Next; }
    return temp;
}

template<class TValue>
typename HierarchicalList<TValue>::iterator& HierarchicalList<TValue>::Iterator::operator+=(size_type n)
{
    for (size_type i = 0; i < n; ++i) {
        if (Node) { Node = Node->Next; }
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
            insertAtHorizon(Arr[i]);
        }
    }
}



template<class TValue>
HierarchicalList<TValue>::HierarchicalList(const HierarchicalList& other) : length(0), Start(nullptr), End()
{
    for (iterator it = other.begin(); it != other.end(); ++it) {
        insertAtHorizon(*it);
    }
}



template<class TValue>
HierarchicalList<TValue>& HierarchicalList<TValue>::operator=(const HierarchicalList& other)
{
    if (this != &other) {
         clear();
         for (iterator it = other.begin(); it != other.end(); ++it) { insertAtHorizon(*it); }
    }
    return *this;
}

template<class TValue>
typename HierarchicalList<TValue>::iterator HierarchicalList<TValue>::begin() const {
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), Start);
}

template<class TValue>
typename HierarchicalList<TValue>::iterator HierarchicalList<TValue>::end() const {
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), nullptr);
}



template<class TValue>
HierarchicalList<TValue>::iterator HierarchicalList<TValue>::find(const reference value) const noexcept
{
    return Iterator(*const_cast<HierarchicalList<TValue>*>(this), findNode(value, Start));  
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
void HierarchicalList<TValue>::insertAtHorizon(const reference value, spNode parent) noexcept
{
    spNode newNode = std::make_shared<Node>(value);
    if (!parent) {
        if (!Start) {
            Start = newNode;
            End = Start;
        }
        else {
            newNode->Next = Start;
            Start = newNode;
        }
    }
    else {
        newNode->Next = parent->Next;
        parent->Next = newNode;
        if (parent == End.lock())
            End = newNode;
    }
    ++length;
}

template<class TValue>
void HierarchicalList<TValue>::insertAtDepth(const reference value, spNode parent) noexcept
{
    spNode newNode = std::make_shared<Node>(value);
    if (!parent) {  insertAtHorizon(value); }
    else {
        spNode child = parent->Down; 
        if (!child) { parent->Down = newNode; }
        else {
            parent->Down = newNode;
            newNode->Down = child;
        }
    }
    ++length;
}

template<class TValue>
void HierarchicalList<TValue>::remove(const reference value) noexcept
{
    if (length == 1) {
        Start = spNode();
        End = Start;
        length--;
    }
    else {
        spNode previous = findPrev(value, Start);
        spNode current;

        if (previous->Next && previous->Next->Value == value)
            current = previous->Next;
        if (previous->Down && previous->Down->Value == value)
            current = previous->Down;

        length -= ((current->Down) ? countByNode(current->Down) : 0) + 1;

        previous->Next = current->Next;
    }
}

template<class TValue>
HierarchicalList<TValue>::spNode HierarchicalList<TValue>::findNode(const reference value, spNode node) const noexcept
{
    if (node->Value == value)
        return node;

    spNode node1 = spNode();
    spNode node2 = spNode();

    if (node->Next)
        node1 = findNode(value, node->Next);
    if (node->Down)
        node2 = findNode(value, node->Down);

    return (node1) ? node1 : node2;
}

template<class TValue>
HierarchicalList<TValue>::spNode HierarchicalList<TValue>::findPrev(const reference value, spNode node) const noexcept
{
    if (node->Next && node->Next->Value == value)
        return node;
    if (node->Down && node->Down->Value == value)
        return node;

    spNode node1 = spNode();
    spNode node2 = spNode();

    if (node->Next)
        node1 = findPrev(value, node->Next);
    if (node->Down)
        node2 = findPrev(value, node->Down);

    return (node1) ? node1 : node2;
}

template<class TValue>
HierarchicalList<TValue>::size_type HierarchicalList<TValue>::countByNode(spNode node, size_type offset) const noexcept
{
    return ((node->Next) ? countByNode(node->Next) : 0) + ((node->Down) ? countByNode(node->Down) : 0) + 1;
}



