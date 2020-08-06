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
        using connection_rule_t = std::vector<std::pair<std::uint32_t, std::uint32_t>>;
        connection_rule_t rule1 {
            std::make_pair(0, 1),
            std::make_pair(0, 2),
            std::make_pair(2, 4),
            std::make_pair(2, 1)
        };
        std::set<std::uint32_t> source1;
        find_source(5, rule1, source1);
        EXPECT_EQ(source1, (std::set<std::uint32_t>{ 0, 3 }));

        connection_rule_t rule2 {
                std::make_pair(0, 3),
                std::make_pair(2, 4),
                std::make_pair(2, 1)
        };
        std::set<std::uint32_t> source2;
        find_source(5, rule2, source2);
        EXPECT_EQ(source2, (std::set<std::uint32_t>{ 0, 2 }));

        connection_rule_t rule3 {
                std::make_pair(0, 1),
                std::make_pair(0, 3),
                std::make_pair(2, 4),
                std::make_pair(2, 1)
        };
        std::set<std::uint32_t> source3;
        find_source(5, rule3, source3);
        EXPECT_EQ(source3, (std::set<std::uint32_t>{ 0, 2 }));
    }

    TEST(ALGORITHM_TEST, IS_ACYCLIC) {
        using connection_rule_t = std::vector<std::pair<std::uint32_t, std::uint32_t>>;

        connection_rule_t  rule1 {
            std::make_pair(0, 2),
            std::make_pair(2, 1),
            std::make_pair(1, 0)
        };
        EXPECT_TRUE(!is_acyclic(3, rule1));

        connection_rule_t rule2 {
            std::make_pair(0, 1),
            std::make_pair(1, 0)
        };

        EXPECT_TRUE(!is_acyclic(2, rule2));
        EXPECT_TRUE(!is_acyclic(3, rule2));

        connection_rule_t rule3 {
            std::make_pair(0, 1),
            std::make_pair(0, 2)
        };
        EXPECT_TRUE(is_acyclic(3, rule3));

        connection_rule_t rule4 {
            std::make_pair(0, 1),
            std::make_pair(1, 2),
            std::make_pair(0, 2)
        };
        EXPECT_TRUE(is_acyclic(3, rule4));

        connection_rule_t rule5 {
            std::make_pair(0, 1),
            std::make_pair(1, 2),
            std::make_pair(0, 2),
            std::make_pair(0, 3)
        };
        EXPECT_TRUE(is_acyclic(4, rule5));

        connection_rule_t rule6 {
                std::make_pair(0, 1),
                std::make_pair(1, 2),
                std::make_pair(0, 2),
                std::make_pair(0, 3),
                std::make_pair(3, 4),
                std::make_pair(4, 0)
        };
        EXPECT_TRUE(!is_acyclic(5, rule6));
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


