#ifndef _PASCAL_
#define _PASCAL_

#include <any>

#include "HierarchicalList.h"
#include "OrderedTable.h"
#include "keywords.h"
#include <sstream>
#include <regex>
#include <set>

namespace Pascal {
    /// <summary>
    /// Парсит код программы в иерархический список
    /// Комментарии в коде парсить не надо
    /// </summary>
    /// <param name="text">Код программы</param>
    /// <param name="list">Список, в который парсится код</param>
    void parseToHierarchicalList(const std::string& text, HierarchicalList<std::string>& list) {
        std::istringstream iss(text);
        std::string line;
        std::regex blockRegex("(program|begin|var|const|end|end.)");
        std::regex commentRegex("(//|\\(\\*)");
        std::smatch match;
        auto it = list.begin();
        while (std::getline(iss, line)) {
            if (std::regex_search(line, match, commentRegex)) {
                std::cout << "!Comment | " << line << std::endl;
                continue;
            }
            if (std::regex_search(line, match, blockRegex)) {
                it++;
                std::cout << "Horizont | " << line << std::endl;
                list.insertAtHorizon(line);
            }
            else {
                /*HierarchicalList<std::string>::spNode firstNode = it.getNode();*/
                /*auto tit = firstNode;*/
                std::cout << "Depth | " << line << std::endl;
                list.insertAtDepth(line, it.getNode()->Down);
            }
        }
    }

//    HierarchicalList<int> myList;
//
//    int value1 = 1;
//    int value2 = 2;
//    int value3 = 3;
//
//    myList.insertAtHorizon(value1);
//    myList.insertAtHorizon(value2);
//    myList.insertAtHorizon(value3);
//
//    auto it = myList.begin();
//    HierarchicalList<int>::spNode firstNode = it.getNode();
//    int value10 = 10;
//    myList.insertAtDepth(value10, firstNode);
//    int value20 = 20;
//    myList.insertAtDepth(value20, firstNode);
//    int value30 = 30;
//    myList.insertAtDepth(value30, firstNode);
//
//    ASSERT_EQ(myList.size(), 6);
//
//    int expectedValues[] = { 30, 20, 10 };
//    size_t index = 0;
//    auto depthIt = firstNode->Down;
//    while (depthIt) {
//        EXPECT_EQ(depthIt->Value, expectedValues[index++]);
//        depthIt = depthIt->Next;
//    }
//}

    //void parseToHierarchicalList(const std::string& text, HierarchicalList<std::string>& list) {
    //    std::istringstream iss(text);
    //    std::string line;
    //    std::regex blockRegex("(program|begin|var|const|end|end.)");
    //    std::regex commentRegex("(//|\\(\\*)"); // Регулярное выражение для определения комментариев
    //    std::smatch match;
    //    while (std::getline(iss, line)) {
    //        if (std::regex_search(line, match, commentRegex)) {
    //            std::cout << "!Comment | " << line << std::endl;
    //            // Пропускаем комментарии
    //            continue;
    //        }
    //        if (std::regex_search(line, match, blockRegex)) {
    //            std::cout << "Horizont | " << line << std::endl;
    //            list.insertAtHorizon(line);
    //        }
    //        else {
    //            // Добавляем целую строку кода в иерархический список
    //            std::cout << "Depth | " << line << std::endl;
    //            list.insertAtDepth(line);
    //        }
    //    }
    //}
    /// <summary>
    /// Парсит блок констант (const) из иерархического списка в таблицу констант
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseVar(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& variables) {
        bool inVarBlock = false;
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it.getNode()->Value == "var") {
                inVarBlock = true;
            }
            else if (inVarBlock && (it.getNode()->Value == "end" || it.getNode()->Value == "end.")) {
                inVarBlock = false;
            }
            else if (inVarBlock) {
                std::string name = it.getNode()->Value;
                variables.Insert(name, std::any());
            }
        }
    }






    

    /// <summary>
    /// Парсит блок переменных (var) из иерархического списка в таблицу переменных
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseConst(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& constants) {
        bool inConstBlock = false;
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (it.getNode()->Value == "const") {
                inConstBlock = true;
            }
            else if (inConstBlock && (it.getNode()->Value == "end" || it.getNode()->Value == "end.")) {
                inConstBlock = false;
            }
            else if (inConstBlock) {
                std::string name = it.getNode()->Value;
                std::string value = it.getNode()->Next->Value; // Предполагается, что значение константы следует сразу за её объявлением
                constants.Insert(name, value);
            }
        }
    }


}

#endif
