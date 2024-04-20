#include <gtest/gtest.h>
#include "SkipList.h"
using namespace std;

TEST(SkipList, Test) {
    SkipList<int> l1;
    auto it = l1.begin();
    auto it2 = l1.end();
    it++;
    if (it == it2)
        std::cout << 1;
}
