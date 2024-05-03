#include <gtest/gtest.h>
#include "Pascal.h"
#include <fstream>
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>
using namespace std;

TEST(Pascal, Test) {

}

TEST(Pascal, ParseSampleFile) {
    ifstream file("../../../pascal--/samples/sample.pmm");
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>());
    file.imbue(utf8_locale);
    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    HierarchicalList<string> list;
    Pascal::parseToHierarchicalList(content, list);

    //list.print();
    OrderedTable<std::string, std::any> constants;
    OrderedTable<std::string, std::any> variables;

    vector<std::string> tmp = Pascal::checkSintax(list);
    Pascal::parseVar(list, variables);
    Pascal::parseConst(list, constants);

    // Пример проверки констант
    ASSERT_TRUE(constants.Find("Pi")); // Проверяем, что в таблице констант есть константа "Pi"
    //ASSERT_EQ(constants.Find('Pi'), "3.1415926"); // Проверяем, что значение константы "Pi" равно "3.1415926"

    // Пример проверки переменных
    ASSERT_TRUE(variables.Find("num1")); // Проверяем, что в таблице переменных есть переменная "num1"
    //ASSERT_EQ(variables.Find("num1"), "integer"); // Проверяем, что тип переменной "num1" равен "integer"

    file.close();
}
