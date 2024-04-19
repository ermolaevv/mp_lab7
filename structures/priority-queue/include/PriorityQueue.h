#ifndef _PRIORITY_QUEUE_
#define _PRIORITY_QUEUE_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <compare>

#include "DHeap.h"

/// <summary>
/// Список с пропусками
/// </summary>
template <class TValue>
class PriorityQueue {
public:
    // Определения типов для совместимости с STL.
    using value_type = TValue;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const reference;
    using size_type = size_t;

protected:
    /// <summary>
    /// Структура-узел.
    /// </summary>
    struct Node {
        size_type Priority;
        value_type Value;

        Node(value_type _value, size_type _priority = 0) : Value(_value), Priority(_priority) {}

        /// <summary>
        /// Spaceship-оператор, обеспечивающий трехсторонне сравнение.
        /// В сравнении учавствует только приоритет!
        /// </summary>
        /// <param name="other">Другой узел</param>
        /// <returns></returns>
        auto operator<=>(const Node& other) const;

        /// <summary>
        /// Проверка равенства узлов.
        /// </summary>
        /// <param name="other">Другой узел</param>
        /// <returns>true, если узлы равны, иначе false</returns>
        bool operator==(const Node& other) const;
    };

    DHeap<Node> Data;

public:

    /// <summary>
    /// Конструктор-обыкновенный.
    /// </summary>
    /// <param name="Arr">Опционально. Указатель на массив данных, которые будут скопированны</param>
    /// <param name="ArrSize">Опционально (обязательно, при использовании Arr). Размер массива данных</param>
    PriorityQueue(pointer Arr = nullptr, size_type ArrSize = 0);

    /// <summary>
    /// Конструктор копирования.
    /// </summary>
    /// <param name="other">Другая приоритетная очередь</param>
    PriorityQueue(const PriorityQueue& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    /// <param name="other">Другая приоритетная очередь</param>
    /// <returns>Возвращает *this</returns>
    PriorityQueue& operator=(const PriorityQueue& other);

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
    /// Очищает очередь.
    /// </summary>
    void clear() const noexcept;

    /// <summary>
    /// Вставить новый элемент в очередь.
    /// </summary>
    /// <param name="value">Значение элемента</param>
    /// <param name="priority">Опционально. Приоритет элемента</param>
    void insert(const reference value, const size_type priority = 0) noexcept;

    /// <summary>
    /// Удалить элемент из начала очерели.
    /// Если очередь пуста, ничего не делать.
    /// </summary>
    /// <param name="value">Элемент списка</param>
    void pop() noexcept;

    /// <summary>
    /// Вывод списка в поток.
    /// </summary>
    /// <param name="os">Поток вывода</param>
    /// <param name="list">Экземпляр списка</param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator<<(std::ostream& os, PriorityQueue& list);
};

#include "../src/PriorityQueue.hpp"

#endif
