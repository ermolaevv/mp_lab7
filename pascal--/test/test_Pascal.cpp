#include <gtest/gtest.h>
#include "Pascal.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

TEST(Pascal, Test) {

}

TEST(Pascal, ParseSampleFile) {
    string filePath = "F:\\repos\\mp-lab7\\mp_lab7\\pascal--\\samples\\sample.pmm";

    ifstream file(filePath);

    stringstream buffer;
    buffer << file.rdbuf();
    string content = buffer.str();

    HierarchicalList<string> list;
    Pascal::parseToHierarchicalList(content, list);

    //list.print();

    file.close();
}
