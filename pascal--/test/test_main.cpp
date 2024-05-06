#include <gtest/gtest.h>
#include <clocale>
#include <Windows.h>
int main(int argc, char **argv) {
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
