#ifndef _HIERARCHICAL_LIST_
#define _HIERARCHICAL_LIST_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <compare>

/// <summary>
/// Иерархический список
/// </summary>
template <class TValue>
class HierarchicalList {
public:
    class Iterator;
    class DepthIterator;

    // Определения типов для совместимости с STL.
    using value_type = TValue;
    using iterator = Iterator;
    using depth_iterator = DepthIterator;
    using const_iterator = const Iterator;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const reference;
    using size_type = size_t;

    struct Node;
    using spNode = std::shared_ptr<Node>;
    using wpNode = std::weak_ptr<Node>;

    /// <summary>
    /// Структура-узел, содержит указатель.
    /// </summary>
    struct Node {
        value_type Value;

        spNode Next;
        spNode Down;

        Node(const reference Value, spNode Next = spNode(), spNode Down = spNode());
    };
protected:
    /// <summary>
    /// Длина списка
    /// </summary>
    size_type length;

    /// <summary>
    /// Начальный узел
    /// </summary>
    spNode Start;

    /// <summary>
    /// Слабый указатель на последний узел.
    /// (Узел, у которого нет узлов в полях Next и Down)
    /// </summary>
    wpNode End;
public:
    /// <summary>
    /// Класс-итератор.
    /// </summary>
    class Iterator {
        HierarchicalList<TValue>& List;

        /// <summary>
        /// Текущий узел, на который указывает объект итератора.
        /// </summary>
        spNode Node;
    public:
        friend class HierarchicalList<value_type>;

        /// <summary>
        /// Конструктор копирования.
        /// </summary>
        /// <param name="it">Другой итератор</param>
        Iterator(const iterator& it);

        /// <summary>
        /// Конструктор-обыкновенный.
        /// </summary>
        /// <param name="list">Ссылка на список</param>
        /// <param name="node">Указатель на узел, с которого начнётся итерация</param>
        Iterator(HierarchicalList<TValue>& list, spNode node);

        /// <summary>
        /// Оператор присваивания.
        /// </summary>
        /// <param name="other">Другой итератор</param>
        /// <returns>Возвращает *this</returns>
        Iterator& operator=(const Iterator& other);

        /// <summary>
        /// При приобразовании к bool, фактически выполняется проверка на конец списка.
        /// </summary>
        operator bool();

        /// <summary>
        /// Spaceship-оператор, обеспечивающий трехсторонне сравнение.
        /// </summary>
        friend auto operator<=>(const iterator& lhs, const iterator& rhs) noexcept
        {
            return rhs.Node <=> lhs.Node;
        }

        /// <summary>
        /// Префиксное смещение итератора вперед.
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator& operator++();

        /// <summary>
        /// Постфиксное смещение итератора вперед.
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator operator++(int);

        /// <summary>
        /// Происзвольное смещение итератора вперед.
        /// </summary>
        /// <param name="n">Величина смещения</param>
        /// <returns>Возвращает *this</returns>
        iterator& operator+=(size_type n);

        /// <summary>
        /// Разыменование итератора.
        /// </summary>
        /// <returns>Ссылка на данные, на которые указывает итератор</returns>
        reference operator*();

        spNode getNode() const { return Node; }
    };

    /// <summary>
    /// Класс-итератор для обхода в глубину.
    /// </summary>
    class DepthIterator {
        HierarchicalList<TValue>& List;

        /// <summary>
        /// Стек узлов для обхода в глубину.
        /// </summary>
        std::vector<spNode> NodeStack;
    public:
        friend class HierarchicalList<value_type>;

        /// <summary>
        /// Конструктор копирования.
        /// </summary>
        DepthIterator(const DepthIterator& it) : List(it.List), NodeStack(it.NodeStack) {}

        /// <summary>
        /// Конструктор-обыкновенный.
        /// </summary>
        DepthIterator(HierarchicalList<TValue>& list, spNode node) : List(list) {
            NodeStack.push_back(node);
        }

        /// <summary>
        /// Оператор присваивания.
        /// </summary>
        DepthIterator& operator=(const DepthIterator& other) {
            if (this != &other) {
                List = other.List;
                NodeStack = other.NodeStack;
            }
            return *this;
        }

        /// <summary>
        /// При приобразовании к bool, фактически выполняется проверка на конец списка.
        /// </summary>
        operator bool() {
            return !NodeStack.empty();

        }

        /// <summary>
        /// Spaceship-оператор, обеспечивающий трехсторонне сравнение.
        /// </summary>
        friend auto operator<=>(const DepthIterator& lhs, const DepthIterator& rhs) noexcept
        {
            return rhs.NodeStack <=> lhs.NodeStack;
        }

        /// <summary>
        /// Префиксное смещение итератора вперед.
        /// </summary>
        DepthIterator& operator++() {
            if (!NodeStack.empty()) {
                spNode node = NodeStack.back();
                NodeStack.pop_back();
                if (node->Down) {
                    NodeStack.push_back(node->Down);
                }
                if (node->Next) {
                    NodeStack.push_back(node->Next);
                }
            }
            return *this;
        }

        /// <summary>
        /// Постфиксное смещение итератора вперед.
        /// </summary>
        DepthIterator operator++(int) {
            DepthIterator temp = *this;
            ++(*this);
            return temp;
        }

        /// <summary>
        /// Разыменование итератора.
        /// </summary>
        reference operator*() {
            assert(!NodeStack.empty());
            return NodeStack.back()->Value;
        }
    };


    /// <summary>
    /// Конструктор-обыкновенный.
    /// Arr будет добавлен в один верхний уровень.
    /// </summary>
    /// <param name="Arr">Опционально. Указатель на массив данных, которые будут скопированны</param>
    /// <param name="ArrSize">Опционально (обязательно, при использовании Arr). Размер массива данных</param>
    HierarchicalList(pointer Arr = nullptr, size_type ArrSize = 0);

    /// <summary>
    /// Конструктор копирования
    /// </summary>
    /// <param name="other">Другой иерархический список</param>
    HierarchicalList(const HierarchicalList& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    /// <param name="other">Другой иерархический список</param>
    /// <returns>Возвращает *this</returns>
    HierarchicalList& operator=(const HierarchicalList& other);

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на первый элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator begin() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на последний элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator end() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на найденный элемент в списке.
    /// </summary>
    /// <returns>Итератор произвольного доступа.</returns>
    iterator find(const reference value) const noexcept;

    /// <summary>
    /// Возвращает количество элементов в списке.
    /// </summary>
    /// <returns>Текущая длина списка.</returns>
    size_type size() const noexcept;

    /// <summary>
    /// Проверяет, пуст ли список.
    /// </summary>
    /// <returns>true значение, если список пуст. false значение, если список не пуст.</returns>
    bool empty() const noexcept;

    /// <summary>
    /// Очищает элементы вектора.
    /// </summary>
    void clear() noexcept;

    /// <summary>
    /// Вставить новый элемент в список
    /// </summary>
    /// <param name="value">Значение для элемента списка</param>
    void insertAtHorizon(const reference value, spNode parent = spNode()) noexcept;

    void insertAtDepth(const reference value, spNode parent = spNode()) noexcept;

    /// <summary>
    /// Удалить элемент по значению.
    /// Если элемента нет в списке, ничего не делать
    /// </summary>
    /// <param name="value">Элемент списка</param>
    void remove(const reference value) noexcept;

    /// <summary>
    /// Вывод списка в поток
    /// </summary>
    /// <param name="os">Поток вывода</param>
    /// <param name="list">Экземпляр списка</param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator<<(std::ostream& os, HierarchicalList& list) {
        typename HierarchicalList<TValue>::spNode current = list.Start;
        os << "HierarchicalList: ";
        while (current != nullptr) {
            os << current->Value << " ";
            current = current->Next;
        }
        return os;
    };

protected:
    spNode findNode(const reference value, spNode node) const noexcept;
    spNode findPrev(const reference value, spNode node) const noexcept;
    size_type countByNode(spNode node, size_type offset = 0) const noexcept;
};

#include "../src/HierarchicalList.hpp"

#endif
