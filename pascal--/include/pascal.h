#ifndef _PASCAL_
#define _PASCAL_

#include <any>

#include "HierarchicalList.h"
#include "OrderedTable.h"
#include "keywords.h"
#include <sstream>
#include <regex>

namespace Pascal {
    /// <summary>
    /// Парсит код программы в иерархический список
    /// Комментарии в коде парсить не надо
    /// </summary>
    /// <param name="text">Код программы</param>
    /// <param name="list">Список, в который парсится код</param>
    void parseToHierarchicalList(const std::string& text, HierarchicalList<std::string>& list) {
        std::regex beginKeyword("\\bbegin\\b");
        std::regex endKeyword("\\bend\\b");
        std::regex programKeyword("\\bprogram\\b");
        std::regex constKeyword("\\bconst\\b");
        std::regex varKeyword("\\bvar\\b");
        std::regex ifKeyword("\\bif\\b");
        std::regex elseKeyword("\\belse\\b");

        std::sregex_iterator it(text.begin(), text.end(), beginKeyword);
        std::sregex_iterator end;

        int currentLevel = 0;

        int previousLevel = 0;

        HierarchicalList<std::string>::spNode currentNode = list.getStart();

        for (; it != end; ++it) {
            std::smatch match = *it;

            if (std::regex_search(match.str(), beginKeyword) || std::regex_search(match.str(), ifKeyword)) {
                ++currentLevel;
            }
            else if (std::regex_search(match.str(), endKeyword)) {
                --currentLevel;
            }

            if (currentLevel != previousLevel) {
                if (currentLevel > previousLevel) {
                    std::string tmp = match.str();
                    list.insertAtDepth(tmp, currentNode);
                    currentNode = list.findNode(tmp, currentNode)->Down;
                }
                else {
                    currentNode = currentNode->Next;
                }
                previousLevel = currentLevel;
            }

            std::string tmp = match.str();
            list.insertAtHorizon(tmp, currentNode);
        }
    }




    /// <summary>
    /// Парсит блок констант (const) из иерархического списка в таблицу констант
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseConst(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& constants) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it.getNode()->Value == "const") {
                ++it;
                while (it != list.end() && it.getNode()->Value != "var" && it.getNode()->Value != "begin") {
                    std::string name, value;
                    std::istringstream iss(it.getNode()->Value);
                    std::getline(iss, name, '=');
                    std::getline(iss, value, ';');
                    constants.Insert(name, value);
                    ++it;
                }
                break;
            }
            ++it;
        }
    }
    

    /// <summary>
    /// Парсит блок переменных (var) из иерархического списка в таблицу переменных
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseVar(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& variables) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it.getNode()->Value == "var") {
                ++it;
                while (it != list.end() && it.getNode()->Value != "begin") {
                    std::string name, type;
                    std::istringstream iss(it.getNode()->Value);
                    std::getline(iss, name, ':');
                    std::getline(iss, type, ';');
                    variables.Insert(name, type);
                    ++it;
                }
                break;
            }
            ++it;
        }
    }
}

#endif
