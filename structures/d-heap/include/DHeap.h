#ifndef _D_HEAP_
#define _D_HEAP_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <compare>
#include <algorithm>

/// <summary>
/// Пирамида.
/// </summary>
template <class TValue>
class DHeap {
public:
    // Определения типов для совместимости с STL.
    using value_type = TValue;
    using iterator = std::vector<value_type>::iterator;
    using const_iterator = std::vector<value_type>::const_iterator;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

protected:
    std::vector<value_type> Data;

    /// <summary>
    /// Максимальное количество потомков.
    /// </summary>
    size_type DescendantCount;

    /// <summary>
    /// Операция "погружене".
    /// </summary>
    /// <param name="index">индекс вершины, нарущающией свойство кучи</param>
    void diving(size_type index);

    /// <summary>
    /// Операция "всплытие".
    /// </summary>
    /// <param name="index">индекс вершины, нарущающией свойство кучи</param>
    void surfacing(size_type index);
public:
    /// <summary>
    /// Конструктор-обыкновенный.
    /// </summary>
    /// <param name="DescendantCount">Опционально. Количество потомков узла в куче</param>
    /// <param name="Arr">Опционально. Указатель на массив данных, которые будут скопированны</param>
    /// <param name="ArrSize">Опционально (обязательно, при использовании Arr). Размер массива данных</param>
    DHeap(size_type DescendantCount = 3, pointer Arr = nullptr, size_type ArrSize = 0);

    /// <summary>
    /// Конструктор копирования.
    /// </summary>
    /// <param name="other">Другая куча</param>
    DHeap(const DHeap& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    /// <param name="other">Другая куча</param>
    /// <returns>Возвращает *this</returns>
    DHeap& operator=(const DHeap& other);

    /// <summary>
    /// Пирамидальная сортировка.
    /// Возвращает отсортированный вектор.
    /// Не портит кучу!
    /// </summary>
    /// <returns>Отсортированный вектор</returns>
    std::vector<value_type> toSortedVector() const noexcept;

    /// <summary>
    /// Получить максимальный элемент кучи.
    /// Не портит кучу!
    /// </summary>
    /// <returns>Ссылка на максимальный элемент</returns>
    const typename DHeap<TValue>::value_type& getMax() const noexcept;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на первый элемент в куче.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator begin() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на последний элемент в куче.
    /// </summary>
    /// <returns>Итератор произвольного доступа</returns>
    iterator end() const;

    /// <summary>
    /// Возвращает итератор произвольного доступа, указывающий на найденный элемент в куче.
    /// </summary>
    /// <returns>Итератор произвольного доступа.</returns>
    const_iterator find(const reference value) const noexcept;

    /// <summary>
    /// Возвращает количество элементов в куче.
    /// </summary>
    /// <returns>Текущая длина кучи.</returns>
    size_type size() const noexcept;

    /// <summary>
    /// Проверяет, пуста ли куча.
    /// </summary>
    /// <returns>true значение, если куча пуста. false значение, если куча не пуста.</returns>
    bool empty() const noexcept;

    /// <summary>
    /// Очищает элементы кучи.
    /// </summary>
    void clear() noexcept;

    /// <summary>
    /// Вставить новый элемент в кучу.
    /// </summary>
    /// <param name="value">Значение для элемента кучи</param>
    void insert(const reference value) noexcept;

    /// <summary>
    /// Удалить элемент по значению.
    /// Если элемента нет в куче, ничего не делать
    /// </summary>
    /// <param name="value">Элемент кучи</param>
    void remove(const reference value) noexcept;

    /// <summary>
    /// Вывод кучи в поток.
    /// </summary>
    /// <param name="os">Поток вывода</param>
    /// <param name="list">Экземпляр кучи</param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator<<(std::ostream& os, DHeap& list);
};

#include "../src/DHeap.hpp"

#endif
