#ifndef _PASCAL_
#define _PASCAL_

#include <any>
#include <sstream>
#include <regex>
#include <set>
#include <unordered_set>
#include "HierarchicalList.h"
#include "OrderedTable.h"
#include "keywords.h"
#include "../../past-labs/postfix/include/MyExpression.h"

namespace Pascal {
    std::string trim(const std::string& str, const std::string& whitespace = " ")
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content
        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;
        return str.substr(strBegin, strRange);
    }

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
            line = trim(line);
            if (line == "")
                continue;
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
            else {
                if (db == false) {
                    /*HierarchicalList<std::string>::spNode firstNode = it.getNode();*/
                    /*auto tit = firstNode;*/
                    /*std::cout << "Depth | " << line << std::endl;*/
                    list.insertAtDepth(line, it.getNode());
                    it.Up();
                }
                if (db == true) {
                    /*std::cout << "Depth | " << line << std::endl;*/
                    it.Down();
                    while (it.getNode()->Next) it++;
                    list.insertAtHorizon(line, it.getNode());
                    it.Up();
                }
                db = true;
            }
        }

        auto insert = [](HierarchicalList<std::string>& list, auto& it2, auto& it3, std::string& buff) -> void {
            if (buff == "")
                return;

            if (*it3 == *it2) {
                /*std::cout << "Depth | " << buff << std::endl;*/
                list.insertAtDepth(buff, it3.getNode());
                it3.Down();
            }
            else {
                /*std::cout << "Horizon | " << buff << std::endl;*/
                list.insertAtHorizon(buff, it3.getNode());
                it3++;
            }
        };

        for (auto it = list.begin(); it != list.end(); it++) {
            it.Down();
            for (auto it2 = it; it2.getNode() != nullptr; it2++) {
                std::string line = *it2;
                std::string buff = "";
                auto it3 = it2;

                char ch;
                for (size_t i = 0; i < line.size(); i++) {
                    ch = line[i];
                    if (ch == ' ') {
                        insert(list, it2, it3, buff);
                        buff = "";
                    }
                    else if (ch == '"') {
                        do {
                            buff += line[i++];
                        } while (line[i] != '"');
                        buff += line[i];
                        insert(list, it2, it3, buff);
                        buff = "";
                    }
                    else if (ch == '(' || ch == ')') {
                        insert(list, it2, it3, buff);
                        buff = ch;
                        insert(list, it2, it3, buff);
                        buff = "";
                    }
                    else if (line[i] == ':' && line[i + 1] == '=') {
                        insert(list, it2, it3, buff);
                        buff = ":=";
                        insert(list, it2, it3, buff);
                        buff = "";
                        i++;
                    }
                    else if (ch == ':' || ch == ',' || ch == ';' || ch == '/' || ch == '+' || ch == '-' || ch == '*' || ch == '=') {
                        insert(list, it2, it3, buff);
                        buff = ch;
                        insert(list, it2, it3, buff);
                        buff = "";
                    }
                    else {
                        buff += ch;
                    }
                }
                if (buff != "")
                    insert(list, it2, it3, buff);

            }
            it.Up();

        }

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

    std::vector<std::string> listtovector(HierarchicalList<std::string>& list) { // Ачё?
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

    bool checkSyntax(const std::vector<std::string>& lines) {
        std::unordered_set<std::string> pascalKeywords = {
"begin", "end", "program", "var", "procedure", "function", "if", "then", "else", "while", "do", "const", "var"
        };

        // Пустые строки. Надо ли оно нам?
        /*for (const auto& line : lines) {
            if (line.empty()) {
                std::cerr << "SYNTAX ERROR | Empty line" << std::endl;
                return false;
            }
        }*/

        // Если нет слов из сета, то проверяем на ";"
        for (const auto& line : lines) {
            bool containsKeyword = false;
            for (const auto& keyword : pascalKeywords) {
                std::regex keywordPattern("\\b" + keyword + "\\b");
                if (std::regex_search(line, keywordPattern) || line == "{" || line == "}") {
                    containsKeyword = true;
                    break; // Прерываем цикл, если найдено ключевое слово
                }
            }
            if (!containsKeyword) {
                if (!std::regex_search(line, std::regex(";"))) {
                    std::cerr << "SYNTAX ERROR | Can't find ';' | " << line << std::endl;
                    return 0;
                }
            }
        }

        // Подсчёт скобок
        //
        int openBrackets = 0;
        int openCurlyBraces = 0;
        for (const auto& line : lines) {
            for (char c : line) {
                if (c == '{') {
                    ++openCurlyBraces;
                }
                else if (c == '}') {
                    --openCurlyBraces;
                }
                if (c == '(') {
                    ++openBrackets;
                }
                else if (c == ')') {
                    --openBrackets;
                }
            }
            if (openCurlyBraces != 0 || openBrackets != 0) {
                std::cerr << "SYNTAX ERROR | () or {} haven't pairs |" << line << std::endl;
                return 0;
            }
        }

        return true;
    }

    void Execute(HierarchicalList<std::string>& list, OrderedTable<std::string, std::any>& constants, OrderedTable<std::string, std::any>& variables) {
        auto strToLower = [](std::string data) {
            std::transform(data.begin(), data.end(), data.begin(),
                [](unsigned char c) { return std::tolower(c); });
            return data;
        };

        auto to_str = [](std::any value) -> std::pair<std::string, std::string> {
            std::string name = value.type().name();
            std::string str_val = "";
            std::string type = "None";
            if (name == "d" || name == "double") {
                str_val = std::to_string(any_cast<double>(value));
                type = "double";
            }
            if (name == "b" || name == "bool") {
                str_val = std::to_string(any_cast<bool>(value));
                type = "bool";
            }
            if (name == "i" || name == "int") {
                str_val = std::to_string(any_cast<int>(value));
                type = "int";
            }
            if (name == "c" || name == "char") {
                str_val = std::to_string(any_cast<char>(value));
                type = "char";
            }
            if (name == "PKc" || name == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >") {
                str_val = any_cast<std::string>(value);
                type = "string";
            }

            return std::make_pair(str_val, type);
        };

        auto to_print = [to_str](OrderedTable<std::string, std::any>& constants, OrderedTable<std::string, std::any>& variables, std::string arg) -> std::string {

            if (arg.starts_with('"')) {
                size_t end = arg.find_last_of('"');
                return arg.substr(1, end - 1);
            }
            else {
                try {
                    std::any val = *constants.Find(arg);
                    return to_str(val).first;
                }
                catch (std::runtime_error) {
                    try {
                        std::any val = *variables.Find(arg);
                        return to_str(val).first;
                    }
                    catch (std::runtime_error) {
                        return "";
                    }
                }
            }
        };

        auto get = [to_str](OrderedTable<std::string, std::any>& constants, OrderedTable<std::string, std::any>& variables, std::string arg) -> std::pair<std::string, std::string> {
            try {
                std::any val = *constants.Find(arg);
                return to_str(val);
            }
            catch (std::runtime_error) {
                try {
                    std::any val = *variables.Find(arg);
                    return to_str(val);
                }
                catch (std::runtime_error) {
                    if (arg.find_first_not_of("0123456789") == std::string::npos)
                        return std::make_pair(arg, "int");
                    else if (arg.find_first_not_of("0123456789,.") == std::string::npos)
                        return std::make_pair(arg, "double");
                    return std::make_pair(std::string(), "None");
                }
            }
        };

        auto split = [](std::string s, std::string delimiter) -> std::vector<std::string> {
            size_t pos_start = 0, pos_end, delim_len = delimiter.length();
            std::string token;
            std::vector<std::string> res;

            while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
                token = s.substr(pos_start, pos_end - pos_start);
                pos_start = pos_end + delim_len;
                res.push_back(token);
            }

            res.push_back(s.substr(pos_start));
            return res;
        };

        auto vec_to_str = [](std::vector<std::string>& vec, std::string delim = "") -> std::string {
            std::ostringstream imploded;
            std::copy(vec.begin(), vec.end(),
                std::ostream_iterator<std::string>(imploded, delim.c_str()));
            return imploded.str();
        };

        auto calc_expr = [get](OrderedTable<std::string, std::any>& constants, OrderedTable<std::string, std::any>& variables, std::string expr) -> double {
            expr = std::regex_replace(std::regex_replace(expr, std::regex("div"), "//"), std::regex("mod"), "%");
            TArithmeticExpression expression(expr);
            auto operands = expression.GetOperands();
            std::map<std::string, double> values;
            for (std::string op : operands) {
                auto p = get(constants, variables, op);

                if (p.second == "int" || p.second == "double") {
                    values.insert(make_pair(op, std::stod(p.first)));
                }

            }
            return expression.Calculate(values);
        };

        auto bool_compare = [vec_to_str, calc_expr](OrderedTable<std::string, std::any>& constants, OrderedTable<std::string, std::any>& variables, std::vector<std::string>& arg) -> bool {
            std::string tmp = vec_to_str(arg, " ");
            return static_cast<bool>(calc_expr(constants, variables, tmp));
        };

        bool flag = false;
        bool skip = false;
        std::string line;
        std::smatch match;
        std::regex walrusOp("\\s*:=\\s*");
        auto it = list.begin();
        while (it != list.end() && it.getNode()->Value != "begin") it++;
        if (it != list.end()) {
            it.Down();
            while (it.getNode()) {
                line = *it;
                if (std::regex_search(line, match, walrusOp)) {
                    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
                    auto splited = split(line, ":=");

                    std::string varName = splited[0];
                    std::string expr = trim(trim(splited[1], ";"));

                    std::any var = *variables.Find(varName);
                    std::string type = var.type().name();

                    if (expr.starts_with('"') &&
                        (type == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >" || type == "PKc"))
                    {
                        variables.Insert(varName, expr);
                    }
                    else if (expr.find_first_not_of("0123456789") == std::string::npos &&
                        (type == "int" || type == "i")) {
                        variables.Insert(varName, std::stoi(expr));
                    }
                    else if (expr.find_first_not_of("0123456789,.") == std::string::npos &&
                        (type == "double" || type == "d")) {
                        variables.Insert(varName, std::stod(expr));
                    }
                    else if (type == "bool" || type == "b") {
                        bool tmp = std::stoi(expr);
                        variables.Insert(varName, tmp);
                    }
                    else if (type == "char" || type == "c") {
                        char ch;
                        if (expr.size() > 1)
                            ch = std::stoi(expr);
                        else
                            ch = expr[0];
                        variables.Insert(varName, ch);
                    }
                    else {
                        
                        double tmp = calc_expr(constants, variables, expr);
                        if (type == "int") {
                            variables.Insert(varName, static_cast<int>(tmp));
                        }
                        else if (type == "double") {
                            variables.Insert(varName, tmp);
                        }
                    }
                }
                else {
                    it.Down();
                    while (it.getNode()) {
                        std::string word = strToLower(*it);
                        if (word == "write") {
                            it += 2;
                            std::string str = *it;
                            std::cout << to_print(constants, variables, str);
                            break;
                        }
                        else if (word == "writeln") {
                            it += 2;
                            std::string str = *it;
                            std::cout << to_print(constants, variables, str) << std::endl;
                            break;
                        }
                        else if (word == "readln") {
                            it += 2;
                            std::string varName = *it;
                            std::any val = *variables.Find(varName);
                            std::string name = val.type().name();
                            //std::cout << varName << " " << name << std::endl;
                            if (name == "d" || name == "double") {
                                double tmp = any_cast<double>(val);
                                std::cin >> tmp;
                                val = tmp;
                            }
                            if (name == "b" || name == "bool") {
                                bool tmp = any_cast<bool>(val);
                                std::cin >> tmp;
                                val = tmp;
                            }
                            if (name == "i" || name == "int") {
                                int tmp = any_cast<int>(val);
                                std::cin >> tmp;
                                val = tmp;
                            }
                            if (name == "c" || name == "char") {
                                char tmp = any_cast<char>(val);
                                std::cin >> tmp;
                                val = tmp;
                            }
                            if (name == "PKc" || name == "class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >")
                            {
                                std::string tmp = any_cast<std::string>(val);
                                std::cin >> tmp;
                                val = tmp;
                            }

                            variables.Insert(varName, val);
                            break;
                        }
                        else if (word == "if") {
                            it += 2;
                            std::vector<std::string> expr;
                            while (*it != ")") expr.push_back(*it++);

                            auto it2 = it;
                            it2.Up();
                            if (bool_compare(constants, variables, expr)) {
                                flag = true;
                                if (!it2.getNode()->Next) {
                                    it2.Up();
                                    it2++;
                                    it2.Down();
                                    it2.Down();
                                    it = it2;
                                    skip = true;
                                }
                            }
                            else {
                                flag = false;
                                if (!it2.getNode()->Next) {
                                    it2.Up();
                                    it2 += 2;
                                    it2.Down();
                                    it2.Down();
                                    it = it2;
                                    skip = true;
                                }
                                else {
                                    it2++;
                                    it2.Down();
                                    it = it2;
                                }
                            }
                            break;
                        }
                        else if (word == "else") {
                            auto it2 = it;
                            it2.Up();
                            if (flag) {
                                if (it2.getNode()->Next) {
                                    it2++;
                                    it2.Down();
                                    it = it2;
                                    skip = true;
                                }
                                else {
                                    it2.Up();
                                    it2 += 2;
                                    it2.Down();
                                    it2.Down();
                                    it = it2;
                                }
                            }
                            else {
                                if (!it2.getNode()->Next) {
                                    it2.Up();
                                    it2++;
                                    it2.Down();
                                    it2.Down();
                                    it = it2;
                                    skip = true;
                                }
                            }
                            break;
                        }
                        else
                            it++;
                    }
                    it.Up();
                }
                if (!skip) {
                    it++;
                }
                else
                    skip = false;
            }
            it.Up();
        }
    }
}

#endif
