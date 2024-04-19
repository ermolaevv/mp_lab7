#ifndef _TABLE_ORDEREDTABLE_
#define _TABLE_ORDEREDTABLE_

#include <iostream>
#include <vector>

#include "VectorTable.h"

/// <summary>
/// Упорядоченная таблица на массиве.
/// </summary>
template <class Key, class Value>
class OrderedTable : public VectorTable<Key,Value> {
public:
    OrderedTable(size_t maxSize = 10000) : VectorTable<Key, Value>(maxSize) { }
    ~OrderedTable() { }

#pragma region Main Methods
    /// <summary>
    /// Поиск записи по ключу.
    /// Если запись найдена, возвращает указатель на значение.
    /// Если запись не найдена, поднимается исключение.
    /// </summary>
    Value* Find(Key key) override;

    /// <summary>
    /// Вставка записи в таблицу.
    /// Если ключ уже существует, его значение будет изменено.
    /// </summary>
    void Insert(Key key, Value value) override;

    /// <summary>
    /// Удаление записи из таблицы.
    /// Если ключа не найдено, поднимается исключение.
    /// </summary>
    void Delete(Key key) override;
#pragma endregion

    /// <summary>
    /// Печать таблицы.
    /// </summary>
    friend std::ostream& operator<<(std::ostream& os, OrderedTable& tab)
    {
        std::cout << "OrderedTable printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/OrderedTable.hpp"

#endif
