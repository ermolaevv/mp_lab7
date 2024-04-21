#ifndef _SKIP_LIST_
#define _SKIP_LIST_

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <compare>

/// <summary>
/// Список с пропусками
/// </summary>
template <class TValue>
class SkipList {
public:
    class Iterator;

    // Определения типов для совместимости с STL.
    using value_type = TValue;
    using iterator = Iterator;
    using const_iterator = const Iterator;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;

protected:
    struct Node;
    using spNode = std::shared_ptr<Node>;
    using wpNode = std::weak_ptr<Node>;

    /// <summary>
    /// Структура-узел.
    /// </summary>
    struct Node {
        value_type Value;
        wpNode Previous;

        /// <summary>
        /// Вектор указателей на следующий узел.
        /// Чем больше индекс, тем выше уровень.
        /// В конструторе выделяется память под все возможные уровни.
        /// </summary>
        std::vector<wpNode> Next;

        Node() : Value(value_type()), Previous(wpNode()), Next(std::vector<wpNode>()){}
        Node(const reference Value, size_type MaxLevel, spNode Previous = spNode());

        /// <summary>
        /// Получить предыдущий узел в списке.
        /// </summary>
        /// <param name="level">Уровень в списке.</param>
        /// <returns>Умный указатель на прошлый узел</returns>
        spNode PreviousOnLevel(size_type level = 0) const;

        /// <summary>
        /// Получить следующий узел в списке.
        /// </summary>
        /// <param name="level">Уровень в списке.</param>
        /// <returns>Умный указатель на следующий узел</returns>
        spNode NextOnLevel(size_type level = 0) const;
    };

    /// <summary>
    /// Максимальный уровень, которого может достигнуть список.
    /// </summary>
    size_type MaxLevel;

    /// <summary>
    /// Длина списка.
    /// </summary>
    size_type length;

    /// <summary>
    /// Начальный узел.
    /// </summary>
    spNode Start;

    /// <summary>
    /// Слабый указатель на последний узел.
    /// </summary>
    wpNode End;

    /// <summary>
    /// Вероятность "выпадения монетки".
    /// (Добавления на уровень)
    /// </summary>
    double coinProbability;
public:
    /// <summary>
    /// Класс-итератор.
    /// </summary>
    class Iterator{
        SkipList<TValue>& List;

		/// <summary>
		/// Текущий узел, на который указывает объект итератора.
		/// </summary>
		spNode Node;
	public:
		friend class SkipList<value_type>;

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
		Iterator(SkipList<TValue>& list, spNode node);

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
        /// Префиксное смещение итератора назад.
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator& operator--();

        /// <summary>
        /// Постфиксное смещение итератора вперед.
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator operator++(int);

        /// <summary>
        /// Постфиксное смещение итератора назад.
        /// </summary>
        /// <returns>Возвращает *this</returns>
        iterator operator--(int);

        /// <summary>
        /// Происзвольное смещение итератора вперед.
        /// </summary>
        /// <param name="n">Величина смещения</param>
        /// <returns>Возвращает *this</returns>
        iterator& operator+=(size_type n);

        /// <summary>
        /// Происзвольное смещение итератора назад.
        /// </summary>
        /// <param name="n">Величина смещения</param>
        /// <returns>Возвращает *this</returns>
        iterator& operator-=(size_type n);

        /// <summary>
        /// Разыменование итератора.
        /// </summary>
        /// <returns>Ссылка на данные, на которые указывает итератор</returns>
        reference operator*();
	};

    /// <summary>
    /// Конструктор-обыкновенный.
    /// </summary>
    /// <param name="MaxLevel">Опционально. Количество уровней в списке</param>
    /// <param name="Probability">Опционально. Вероятность "выпадения монетки"</param>
    /// <param name="Arr">Опционально. Указатель на массив данных, которые будут скопированны</param>
    /// <param name="ArrSize">Опционально (обязательно, при использовании Arr). Размер массива данных</param>
    SkipList(size_type MaxLevel = 3, double Probability = 1.0/4.0, pointer Arr = nullptr, size_type ArrSize = 0);

    /// <summary>
    /// Конструктор копирования.
    /// </summary>
    /// <param name="other">Другой список</param>
    SkipList(const SkipList& other);

    /// <summary>
    /// Оператор присваивания.
    /// </summary>
    /// <param name="other">Другой список с пропусками</param>
    /// <returns>Возвращает *this</returns>
    SkipList& operator=(const SkipList& other);

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
    /// Очищает элементы списка.
    /// </summary>
    void clear() const noexcept;

    /// <summary>
    /// Вставить новый элемент в список.
    /// </summary>
    /// <param name="value">Значение для элемента списка</param>
    void insert(const reference value) noexcept;

    /// <summary>
    /// Удалить элемент по значению.
    /// Если элемента нет в списке, ничего не делать
    /// </summary>
    /// <param name="value">Элемент списка</param>
    void remove(const reference value) noexcept;

    /// <summary>
    /// Вывод списка в поток.
    /// </summary>
    /// <param name="os">Поток вывода</param>
    /// <param name="list">Экземпляр списка</param>
    /// <returns>Поток вывода</returns>
    friend std::ostream& operator<<(std::ostream& os, SkipList& list);
};

#include "../src/SkipList.hpp"

#endif
