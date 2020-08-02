//
// Created by hungr on 2020/08/03.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "graph_algorithm.h"

bool operator==(const std::set<std::uint32_t>& s1, const std::set<std::uint32_t>& s2) {
    auto iter1 = s1.begin(), iter2 = s2.begin();
    for(; iter1 != s1.end() && iter2 != s2.end(); iter1++, iter2++) {
        if(*iter1 != *iter2) return false;
    }
    return iter1 == s1.end() && iter2 == s2.end();
}

namespace {
    TEST(ALGORITHM_TEST, OPERATOR_EQUAL) {
        EXPECT_TRUE((std::set<std::uint32_t> {1, 2, 3, 4} == std::set<std::uint32_t> {1, 2, 3, 4}));
        EXPECT_TRUE((std::set<std::uint32_t> {1, 2, 4, 3} == std::set<std::uint32_t> {1, 2, 3, 4}));
        EXPECT_TRUE(!(std::set<std::uint32_t> {1, 3, 3, 4} == std::set<std::uint32_t> {1, 2, 3, 4}));
        EXPECT_TRUE(!(std::set<std::uint32_t> {1, 5, 3, 4} == std::set<std::uint32_t> {1, 2, 3, 4}));
    }

    TEST(ALGORITHM_TEST, FIND_SOURCE) {

    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


