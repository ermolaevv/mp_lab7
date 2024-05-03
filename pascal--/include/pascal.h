#ifndef _PASCAL_
#define _PASCAL_

#include <any>

#include "HierarchicalList.h"
#include "OrderedTable.h"
#include "keywords.h"
#include <sstream>
#include <regex>
#include <set>
#include <vector>

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
        bool tb = false;
        bool db = false;
        auto it = list.begin();
        while (std::getline(iss, line)) {
            if (std::regex_search(line, match, commentRegex)) {
                /*std::cout << "!Comment | " << line << std::endl;*/
                continue;
            }
            if (std::regex_search(line, match, blockRegex) && tb == false) {
                /*std::cout << "Horizont | " << line << std::endl;*/
                    list.insertAtHorizon(line);
                    tb = true;
                    it = list.begin();
                    db = false;
            }
            else if (std::regex_search(line, match, blockRegex) && tb == true) {
                /*std::cout << "Horizont | " << line << std::endl;*/
                    list.insertAtHorizon(line, it.getNode());
                    db = false;
                    it++;
            }
            else if(line != ""){
                if (db == false) {
                    /*HierarchicalList<std::string>::spNode firstNode = it.getNode();*/
                    /*auto tit = firstNode;*/
                    /*std::cout << "Depth | " << line << std::endl;*/
                    list.insertAtDepth(line, it.getNode());
                    it.Up(); //!!!!!!!!!!!!!!!!!!!
                }
                if (db == true) {
                    /*std::cout << "Depth | " << line << std::endl;*/
                    list.insertAtHorizon(line, it.getNode()->Down);
                    /*it.Up();*/
                }
                db = true;
            }
        }
    }

    std::vector<std::string> checkSintax(HierarchicalList<std::string>& list) {
        std::vector<std::string> vector;
        bool t = false;
        for (auto it = list.begin(); it != list.end(); ++it) {
            t = false;
            vector.push_back(it.getNode()->Value);
            it.Down();
            while (it != list.end()) {
                t = true;
                vector.push_back(it.getNode()->Value);
                //vector.push_back(it.getNode()->Value);
                it++;
            }
            //if (t == true)
                it.Up();
            
            
        }
        return vector;
    }

    /// <summary>
    /// Парсит блок констант (const) из иерархического списка в таблицу констант
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseVar(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& variables) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it.getNode()->Value == "var") {
                it.Down();
                while (it != list.end() && it.getNode()->Value != "begin") {
                    std::string tmp = it.getNode()->Value;
                    // Очистка от пробелов, кроме тех, которые в кавычках
                    bool delete_spaces = true, start = false;
                    std::string new_str = "";
                    for (unsigned int i = 0; i < tmp.size(); ++i) {
                        if (tmp[i] == '\"') {
                            start ? start = false : start = true;
                            if (start) {
                                delete_spaces = false;
                            }
                        }
                        if (!start) {
                            delete_spaces = true;
                        }
                        if (delete_spaces) {
                            if (tmp[i] != ' ') {
                                new_str += tmp[i];
                            }
                        }
                        else {
                            new_str += tmp[i];
                        }
                    }
                    //-------------------------------------------------------
                    std::istringstream iss(new_str);
                    // Извлечение типа данных и проверка на =
                    char tch = ':';
                    std::size_t pos = new_str.find(tch);
                    std::string subString = new_str.substr(pos + 1);
                    subString.pop_back(); // Удаление ;
                    pos = new_str.find('=');
                    bool result = false;
                    std::string tresult;
                    if (pos != std::string::npos) {
                        result = true;
                        tresult = new_str.substr(pos+1);
                        tresult.pop_back();
                        pos = subString.find('=');
                        subString = subString.substr(0, pos);
                    }
                    // -----------------------------------------------------
                    std::string var;
                    std::string tmpstr = iss.str();
                    std::size_t tpos = tmpstr.find(':');
                    tmpstr = tmpstr.substr(0,tpos);
                    /*while (std::getline(iss, var, ':')) {*/
                        std::istringstream iss_var(tmpstr);
                        std::string var_name;
                        std::string type = subString;
                        while (std::getline(iss_var, var_name, ',')) {
                            std::any value;
                            if (result == true) {
                                if (type == "double") {
                                    value = std::stod(tresult);
                                }
                                else if (type == "integer") {
                                    value = std::stoi(tresult);
                                }
                                else if (type == "boolean") {
                                    /*if (var_value == "1") // Возможно такого объявления нет в паскале, надо разбираться
                                        value = true;
                                    if (var_value == "0")
                                        value = false;*/
                                    if (tresult == "True")
                                        value = true;
                                    if (tresult == "False")
                                        value = false;
                                    else
                                        value = false;
                                }
                                else if (type == "string") {
                                    value = (tresult);
                                }
                                else if (type == "char") {
                                    value = char(tresult[0]);
                                }
                            }
                            else { // Значение по умолчанию
                                if (type == "double") {
                                    value = double();
                                }
                                else if (type == "integer") {
                                    value = int();
                                }
                                else if (type == "boolean") {
                                    value = bool();
                                }
                                else if (type == "string") {
                                    value = std::string();
                                }
                                else if (type == "char") {
                                    value = char();
                                }
                                
                            }
                            variables.Insert(var_name, value);
                        }
                        //}
                    it++;
                }
            }
            it++;
        }
    }

    /// <summary>
    /// Парсит блок переменных (var) из иерархического списка в таблицу переменных
    /// Если блок отсутствует, ничего не делать
    /// </summary>
    /// <param name="list">Список, содержащий код</param>
    /// <param name="constants">Таблица констант</param>
    void parseConst(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& constants) {
        auto it = list.begin();
        while (it != list.end()) {
            if (it.getNode()->Value == "const") {
                it.Down();
                while (it != list.end() && it.getNode()->Value != "begin") {
                    std::string tmp = it.getNode()->Value;
                    // Очистка от пробелов, кроме тех, которые в кавычках
                    bool delete_spaces = true, start = false;
                    std::string new_str = "";
                    for (unsigned int i = 0; i < tmp.size(); ++i) {
                        if (tmp[i] == '\"') {
                            start ? start = false : start = true;
                            if (start) {
                                delete_spaces = false;
                            }
                        }
                        if (!start) {
                            delete_spaces = true;
                        }
                        if (delete_spaces) {
                            if (tmp[i] != ' ') {
                                new_str += tmp[i];
                            }
                        }
                        else {
                            new_str += tmp[i];
                        }
                    }
                    //-------------------------------------------------------
                    std::istringstream iss(new_str);
                    // Извлечение типа данных и проверка на =
                    char tch = ':';
                    std::size_t pos = new_str.find(tch);
                    std::string subString = new_str.substr(pos + 1);
                    subString.pop_back(); // Удаление ;
                    pos = new_str.find('=');
                    bool result = false;
                    std::string tresult;
                    if (pos != std::string::npos) {
                        result = true;
                        tresult = new_str.substr(pos + 1);
                        tresult.pop_back();
                        pos = subString.find('=');
                        subString = subString.substr(0, pos);
                    }
                    // -----------------------------------------------------
                    std::string var;
                    std::string tmpstr = iss.str();
                    std::size_t tpos = tmpstr.find(':');
                    tmpstr = tmpstr.substr(0, tpos);
                    /*while (std::getline(iss, var, ':')) {*/
                    std::istringstream iss_var(tmpstr);
                    std::string var_name;
                    std::string type = subString;
                    while (std::getline(iss_var, var_name, ',')) {
                        std::any value;
                        if (result == true) { 
                            if (type == "double") {
                                value = std::stod(tresult);
                            }
                            else if (type == "integer") {
                                value = std::stoi(tresult);
                            }
                            else if (type == "boolean") {
                                /*if (var_value == "1") // Возможно такого объявления нет в паскале, надо разбираться
                                    value = true;
                                if (var_value == "0")
                                    value = false;*/
                                if (tresult == "True")
                                    value = true;
                                if (tresult == "False")
                                    value = false;
                                else
                                    value = false;
                            }
                            else if (type == "string") {
                                value = (tresult);
                            }
                            else if (type == "char") {
                                value = char(tresult[0]);
                            }
                        }
                        constants.Insert(var_name, value);
                    }
                    /* }*/
                    it++;
                }
            }
            it++;
        }
    }
}

#endif
