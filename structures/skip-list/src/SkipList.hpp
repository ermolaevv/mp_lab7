#include "SkipList.h"
template<class TValue>
SkipList<TValue>::Node::Node(const reference Value, size_type MaxLevel, spNode Previous): Value(Value), Previous(Previous)
{
    Next.resize(MaxLevel);
}

template<class TValue>
SkipList<TValue>::spNode SkipList<TValue>::Node::PreviousOnLevel(size_type level) const
{
    if (!Previous.expired()) { return Previous.lock(); }
    return spNode;
}

template<class TValue>
SkipList<TValue>::spNode SkipList<TValue>::Node::NextOnLevel(size_type level) const
{
    if (level < Next.size() && !Next[level].expired()) { return Next[level].lock(); }
    return spNode();
}

template<class TValue>
SkipList<TValue>::Iterator::Iterator(const iterator& it): List(it.List), Node(it.Node) {}

template<class TValue>
SkipList<TValue>::Iterator::Iterator(SkipList<TValue>& list, spNode node): List(list), Node(node) {}

template<class TValue>
typename SkipList<TValue>::Iterator& SkipList<TValue>::Iterator::operator=(const Iterator& other)
{
    if (this != &other) { Node = other.Node; }
    return *this;
}

template<class TValue>
SkipList<TValue>::Iterator::operator bool() { return Node != nullptr; }

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator++()
{
    if (Node) { Node = Node->NextOnLevel(0); }
    return *this;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator--()
{
    if (Node) { Node = Node->PreviousOnLevel(0); }
    return *this;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::Iterator::operator--(int)
{
    Iterator temp = *this;
    --(*this);  
    return temp;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator+=(size_type n)
{
    while (n > 0 && Node) {
        Node = Node->NextOnLevel(0);
        n--;
    }
    return *this;
}

template<class TValue>
typename SkipList<TValue>::iterator& SkipList<TValue>::Iterator::operator-=(size_type n)
{
    while (n > 0 && Node) {
        Node = Node->PreviousOnLevel(0);
        n--;
    }
    return *this;
}

template<class TValue>
SkipList<TValue>::reference SkipList<TValue>::Iterator::operator*()
{
    auto lockedNode = Node.lock(); 
    assert(lockedNode != nullptr); 
    return lockedNode->Value;
}

template<class TValue>
SkipList<TValue>::SkipList(size_type MaxLevel, double Probability, pointer Arr, size_type ArrSize): MaxLevel(MaxLevel), coinProbability(Probability), length(0)
{
    Start = std::make_shared<Node>(); 
    End = std::make_shared<Node>();
    if (Arr != nullptr && ArrSize > 0) {
        for (size_type i = 0; i < ArrSize; i++) { insert(Arr[i]); }
    }
}

template<class TValue>
SkipList<TValue>::SkipList(const SkipList& other): MaxLevel(other.MaxLevel), coinProbability(other.coinProbability), length(0)
{
    Start = std::make_shared<Node>(); 
    End = std::make_shared<Node>();
    for (iterator it = other.begin(); it != other.end(); it++) { insert(*it); }
    
    /*catch (const std::exception& e) {
        std::cerr("Error of copy-constructor: ") << e.what() << std::endl;
        clear();
        throw;
    }*/
}

template<class TValue>
SkipList<TValue>& SkipList<TValue>::operator=(const SkipList& other)
{
    if (this != *other) {
        clear();
        MaxLevel = other.MaxLevel;
        coinProbability = other.coinProbability;
        for (iterator it = other.begin(); it != other.end(); it++) { insert(*it); }
    }
    return *this;
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::begin() const
{
    return iterator(const_cast<SkipList<TValue>&>(*this), this->Start);
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::end() const
{
    return iterator(const_cast<SkipList<TValue>&>(*this), this->End.lock());
}

template<class TValue>
SkipList<TValue>::iterator SkipList<TValue>::find(const reference value) const noexcept
{
    for (auto it = begin(); it != end(); it++) { if (*it == value) { return it;} }
    return end();
}

template<class TValue>
SkipList<TValue>::size_type SkipList<TValue>::size() const noexcept
{
    return length;
}

template<class TValue>
bool SkipList<TValue>::empty() const noexcept
{
    return length == 0;
}

template<class TValue>
void SkipList<TValue>::clear() const noexcept
{
    Node* current = Start;
    while (current != nullptr) {
        Node* temp = current->NextOnLevel(0).lock();
        delete current;
        current = temp;
    }
    Start = End = nullptr;
    length = 0;
}

template<class TValue>
void SkipList<TValue>::insert(const reference value) noexcept
{
    std::vector<spNode*> update(MaxLevel+1, nullptr);
    spNode current = Start;
    for (int i = MaxLevel; i >= 0; i--) {
        while (current && current->NextOnLevel(i) && current->NextOnLevel(i)->Value < value) {  current = current->NextOnLevel(i); }
        update[i] = &current;
    }
    int newNodeLevel = 0;
    while (newNodeLevel < MaxLevel && (rand() % 100) < (coinProbability * 100)) { newNodeLevel++; }
    spNode newNode = std::make_shared<Node>(value, newNodeLevel);
    for (int i = 0; i <= newNodeLevel; i++) {
        if (*update[i]) {
            newNode->Next[i] = (*update[i])->NextOnLevel(i);
            (*update[i])->Next[i] = newNode;
        }
        else {
            newNode->Next[i] = Start;
        }
    }
    if (!Start || Start->Value > value) {
        Start = newNode;
    }
    length++;
}

template<class TValue>
void SkipList<TValue>::remove(const reference value) noexcept
{
    std::vector<spNode*> update(MaxLevel + 1, nullptr);
    spNode current = Start;
    for (int i = MaxLevel; i >= 0; i--) {
        while (current && current->NextOnLevel(i) && current->NextOnLevel(i)->Value < value) { current = current->NextOnLevel(i); }
        update[i] = &current;
    }
    current = current->NextOnLevel(0); 
    if (current && current->Value == value) {
        for (int i = 0; i <= MaxLevel; i++) {
            if (update[i] && (*update[i])->NextOnLevel(i) == current) { (*update[i])->NextOnLevel(i) = current->NextOnLevel(i); }
        }
        if (Start == current) { Start = current->NextOnLevel(0); }
        length--; 
    }
}

template<class TValue>
std::ostream& operator<<(std::ostream& os, SkipList<TValue>& list)
{
    for (auto it = list.begin(); it != list.end(); it++) { os << *it << " "; }
    return os;
}
