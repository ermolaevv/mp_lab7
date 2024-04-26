#ifndef _PASCAL_
#define _PASCAL_

#include <any>

#include "HierarchicalList.h"
#include "OrderedTable.h"
#include "keywords.h"

namespace Pascal {
    /// <summary>
    /// Парсит код программы в иерархический список
    /// Комментарии в коде парсить не надо
    /// </summary>
    /// <param name="text">Код программы</param>
    /// <param name="list">Список, в который парсится код</param>
    void parseToHierarchicalList(const std::string& text, HierarchicalList<std::string>& list) {
        ;
    }

    /// <summary>
    /// Парсит блок констант (const) из иерархического списка в таблицу констант
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseConst(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& constants) {
        ;
    }

    /// <summary>
    /// Парсит блок переменных (var) из иерархического списка в таблицу переменных
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseVar(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& variables) {
        ;
    }
}

#endif
