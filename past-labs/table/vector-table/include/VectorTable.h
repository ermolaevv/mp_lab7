#ifndef _TABLE_VECTORTABLE_
#define _TABLE_VECTORTABLE_

#include <iostream>
#include <vector>

#include "Table.h"

/// <summary>
/// Линейная таблица на массиве.
/// </summary>
template <class Key, class Value>
class VectorTable : public Table<Key,Value> {
protected:
    mutable std::vector<typename Table<Key, Value>::template STableRec<Key, Value>> data;
public:
    VectorTable(size_t maxSize = 10000) : Table<Key, Value>(maxSize) { }
    ~VectorTable() { }

#pragma region Info Methods
    /// <summary>
    /// Возращает количество записей (длину таблицы).
    /// </summary>
    size_t GetDataCount() const noexcept override { return data.size(); }

    /// <summary>
    /// Проверка таблицы на пустоту.
    /// Если длина таблицы равна нулю, возвращает true.
    /// </summary>
    bool IsEmpty() const noexcept override { return data.size() == 0; }

    /// <summary>
    /// Проверка таблицы на заполненность.
    /// Если длина таблицы равна maxSize, возвращает true.
    /// </summary>
    bool IsFull() const noexcept override { return data.size() == this->maxSize; }
#pragma endregion

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
    /// Вставка записи в таблицу.
    /// Если ключ уже существует, поднимается исключение.
    /// </summary>
    void Delete(Key key) override;
#pragma endregion

#pragma region Navigate
    /// <summary>
    /// Проверка окончания таблицы.
    /// Если таблица кончилась, то возращает true.
    /// </summary>
    bool IsTabEnded(void) const noexcept override;

    /// <summary>
    /// Переход к следующей записи. После применения к последней записи, переходит к первой.
    /// Возвращает новую позицию.
    /// </summary>
    size_t GoNext(void) noexcept override;

#pragma region Access
    /// <summary>
    /// Получить ключ активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    Key GetKey(void) const override;

    /// <summary>
    /// Получить значение активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    Value* GetValuePtr(void) const override;
#pragma endregion

    /// <summary>
    /// Печать таблицы.
    /// </summary>
    friend std::ostream& operator<<(std::ostream& os, VectorTable& tab)
    {
        std::cout << "VectorTable printing" << std::endl;
        for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#include "../src/VectorTable.hpp"

#endif
