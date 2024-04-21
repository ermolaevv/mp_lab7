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
    assert(Node != nullptr); 
    return Node->Value; 
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
    if (this != &other) {
        SkipList<TValue> temp(other.MaxLevel, other.coinProbability); 

        for (iterator it = other.begin(); it != other.end(); ++it) {
            temp.insert(*it); 
        }
        std::swap(MaxLevel, temp.MaxLevel);
        std::swap(coinProbability, temp.coinProbability);
        std::swap(Start, temp.Start);
        std::swap(End, temp.End);
        std::swap(length, temp.length);
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
void SkipList<TValue>::clear() noexcept
{
    spNode current = Start;
    while (current != nullptr) {
        spNode temp = current->NextOnLevel(0);
        current.reset(); 
        current = temp; 
    }
    Start.reset(); 
    End.reset(); 
    length = 0;
}


template<class TValue>
void SkipList<TValue>::insert(const reference value) noexcept
{
    std::vector<spNode*> update(MaxLevel + 1, nullptr);
    spNode current = Start;

    for (int i = MaxLevel; i >= 0; i--) {
        while (current->NextOnLevel(i) && current->NextOnLevel(i)->Value < value) { current = current->NextOnLevel(i); }
        update[i] = &current;
    }

    int newNodeLevel = 0;
    while (newNodeLevel < MaxLevel && (rand() % 100) < (coinProbability * 100)) { newNodeLevel++; }

    if (newNodeLevel > MaxLevel) { MaxLevel = newNodeLevel; }

    spNode newNode = std::make_shared<Node>(value, newNodeLevel);
    for (int i = 0; i <= newNodeLevel; i++) {
        newNode->NextOnLevel(i) = (*update[i])->NextOnLevel(i);
        (*update[i])->NextOnLevel(i) = newNode;
    }
    length++;
}



template<class TValue>
void SkipList<TValue>::remove(const reference value) noexcept
{
    std::vector<spNode*> update(MaxLevel + 1, nullptr);
    spNode current = Start;

    for (int i = MaxLevel; i >= 0; i--) {
        while (current->NextOnLevel(i) && current->NextOnLevel(i)->Value < value) { current = current->NextOnLevel(i); }
        update[i] = &current;
    }

    current = current->NextOnLevel(0);
    if (current && current->Value == value) {
        std::cout << "Found element to remove: " << current->Value << std::endl;

        for (int i = 0; i <= MaxLevel; i++) {
            if (*update[i] && (*update[i])->NextOnLevel(i) == current) {
                std::cout << "Removing element from level " << i << std::endl;
                (*update[i])->NextOnLevel(i) = current->NextOnLevel(i);
            }
        }
        if (Start == current) {
            std::cout << "Updating Start pointer" << std::endl;
            Start = current->NextOnLevel(0);
        }

        while (MaxLevel > 0 && !Start->NextOnLevel(MaxLevel - 1)) {
            std::cout << "Decreasing MaxLevel to " << (MaxLevel - 1) << std::endl;
            MaxLevel--;
        }
    }
    length--;
}






template<class TValue>
std::ostream& operator<<(std::ostream& os, SkipList<TValue>& list)
{
    for (auto it = list.begin(); it != list.end(); it++) { os << *it << " "; }
    return os;
}
