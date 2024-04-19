#ifndef _TABLE_TABLE_
#define _TABLE_TABLE_

#include <iostream>

/// <summary>
/// Базовый класс таблиц. Абстрактный класс.
/// </summary>
template <class Key, class Value>
class Table {
protected:
    /// <summary>
    /// Шаблонная стркутура табличной записи.
    /// </summary>
    template <class Key, class Value>
    struct STableRec {
        Key key;
        Value value;
        STableRec(Key key, Value value) {
            this->key = key;
            this->value = value;
        }
        STableRec() : key(Key()), value(Value()) {}
    };

    /// <summary>
    /// Текущая позиция (в записях).
    /// </summary>
    size_t position = 0;

    /// <summary>
    /// Максимальное количество записей.
    /// </summary>
    size_t maxSize;
public:
    Table(size_t maxSize = 10000) { this->maxSize = maxSize; }

#pragma region Info Methods
    /// <summary>
    /// Возращает количество записей (длину таблицы).
    /// </summary>
    virtual size_t GetDataCount() const noexcept = 0;

    /// <summary>
    /// Проверка таблицы на пустоту.
    /// Если длина таблицы равна нулю, возвращает true.
    /// </summary>
    virtual bool IsEmpty() const noexcept = 0;

    /// <summary>
    /// Проверка таблицы на заполненность.
    /// Если длина таблицы равна maxSize, возвращает true.
    /// </summary>
    virtual bool IsFull() const noexcept = 0;
#pragma endregion

#pragma region Main Methods
    /// <summary>
    /// Поиск записи по ключу.
    /// Если запись найдена, возвращает указатель на значение.
    /// Если запись не найдена, поднимается исключение.
    /// </summary>
    virtual Value* Find(Key key) = 0;

    /// <summary>
    /// Вставка записи в таблицу.
    /// Если ключ уже существует, его значение будет изменено.
    /// </summary>
    virtual void Insert(Key key, Value value) = 0;

    /// <summary>
    /// Удаление записи из таблицы.
    /// Если ключа не найдено, поднимается исключение.
    /// </summary>
    virtual void Delete(Key key) = 0;
#pragma endregion

#pragma region Navigate

    /// <summary>
    /// Устанавливает текущую позицию на первую запись
    /// Возвращает 0
    /// </summary>
    virtual size_t Reset(void) noexcept
    {
        this->position = 0;
        return 0;
    };

    /// <summary>
    /// Проверка окончания таблицы.
    /// Если таблица кончилась, то возращает true.
    /// </summary>
    virtual bool IsTabEnded(void) const noexcept = 0;

    /// <summary>
    /// Переход к следующей записи. После применения к последней записи, переходит к первой.
    /// Возвращает новую позицию.
    /// </summary>
    virtual size_t GoNext(void) noexcept = 0;
#pragma endregion

#pragma region Access
    /// <summary>
    /// Получить ключ активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    virtual Key GetKey(void) const = 0;

    /// <summary>
    /// Получить значение активной записи.
    /// Если ключ не найден, поднимается исключение.
    /// </summary>
    virtual Value* GetValuePtr(void) const = 0;


#pragma endregion
    // Печать таблицы
    friend std::ostream& operator<<(std::ostream& os, Table& tab)
    {
        std::cout << "Table printing" << std::endl;
        tab.Reset();
        for (size_t i = 0; i < tab.GetDataCount(); i++, tab.GoNext())
        {
            os << " Key: " << tab.GetKey() << " Val: " << *tab.GetValuePtr() << std::endl;
        }
        return os;
    }
};

#endif
