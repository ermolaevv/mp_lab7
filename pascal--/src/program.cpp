#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <windows.h>
#include <codecvt>
#include <locale>

#include "pascal.h"

using namespace Pascal;

enum Mode {
    READ_FILE,
    TEXT
};

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    Mode currentMode = TEXT;
    std::string filename, text;
    HierarchicalList<std::string> Hlist;
    OrderedTable<std::string, std::any> constants, variables;

    if (argc == 1) {
        return 0;
    }
    if (argc == 2) {
        text = std::string(argv[1]);
    }
    else {
        for (size_t i = 1; i < argc; i++) {
            if (_stricmp(argv[i], "/f") == 0) {
                filename = std::string(argv[++i]);
                currentMode = READ_FILE;
                continue;
            }
            else {
                std::cerr << "Error flag: " + std::string(argv[i]);
                exit(-1);
            }
        }
    }

    if (currentMode == READ_FILE) {
        std::ifstream file(filename, std::ios_base::in);

        if (!file.is_open()) {
            std::cerr << "Error while openning file";
            exit(-1);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        text = buffer.str();

        file.close();
    }

    parseToHierarchicalList(text, Hlist);
    parseConst(Hlist, constants);
    parseVar(Hlist, variables);

    try {
        Execute(Hlist, constants, variables);
    }
        catch (std::exception e) {
        std::cerr << e.what();
    }

}
