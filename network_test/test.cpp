//
// Created by hungr on 2020/08/03.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "graph_algorithm.h"
#include "cgp_feedforward.h"
#include "devnetwork.h"

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

    TEST(CLASS_TEST, CGP_FEEDFORWARD) {
        auto add = [](const std::vector<float>& v) { return v[0] + v[1]; };
        auto sub = [](const std::vector<float>& v) { return v[0] - v[1]; };
        auto mul = [](const std::vector<float>& v) { return v[0] * v[1]; };
        auto div = [](const std::vector<float>& v) { return v[1] != 0 ? (v[0] / v[1]) : 0; };
        cgp_feedforward_config config1 {
            3, 2,
            std::make_pair(0, 0),
            std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
            std::vector<std::uint32_t> {},
            std::vector<std::uint32_t> {},
            std::vector<std::uint32_t> { 0, 1 }
        };

        cgp_feedforward n1(config1);
        n1.input(std::vector<float> { 1.0f, 1.2f, 3.2f });
        auto o1 = n1.get_outputs();
        EXPECT_FLOAT_EQ(o1[0], 1.0f);
        EXPECT_FLOAT_EQ(o1[1], 1.2f);

        n1.input(std::vector<float> { 2.0f, 3.2f, 1.0f});
        auto o2 = n1.get_outputs();
        EXPECT_FLOAT_EQ(o2[0], 2.0f);
        EXPECT_FLOAT_EQ(o2[1], 3.2f);

        cgp_feedforward_config config2 {
                3, 2,
                std::make_pair(1, 1),
                std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
                std::vector<std::uint32_t> { 1 },
                std::vector<std::uint32_t> { 0, 1 },
                std::vector<std::uint32_t> { 3, 2 },
        };

        cgp_feedforward n2(config2);
        n2.input(std::vector<float> { 1.0f, 2.0f, 3.0f });
        auto o3 = n2.get_outputs();
        EXPECT_FLOAT_EQ(o3[0], -1.0f);
        EXPECT_FLOAT_EQ(o3[1], 3.0f);

        n2.input(std::vector<float> { 2.0f, 1.0f, 3.2f });
        auto o4 = n2.get_outputs();
        EXPECT_FLOAT_EQ(o4[0], 1.0f);
        EXPECT_FLOAT_EQ(o4[1], 3.2f);

        cgp_feedforward_config config3 {
                3, 2,
                std::make_pair(1, 2),
                std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
                std::vector<std::uint32_t> { 1, 2 },
                std::vector<std::uint32_t> { 0, 1, 1, 2 },
                std::vector<std::uint32_t> { 4, 3 },
        };
        cgp_feedforward n3(config3);

        n3.input(std::vector<float> { 1.0f, 2.0f, 3.0f });
        auto o5 = n3.get_outputs();
        EXPECT_FLOAT_EQ(o5[0], 6.0f);
        EXPECT_FLOAT_EQ(o5[1], -1.0f);

        n3.input(std::vector<float> { 2.2f, 1.0f, 3.2f });
        auto o6 = n3.get_outputs();
        EXPECT_FLOAT_EQ(o6[0], 3.2f);
        EXPECT_FLOAT_EQ(o6[1], 1.2f);

        cgp_feedforward_config config4 {
                3, 2,
                std::make_pair(2, 1),
                std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
                std::vector<std::uint32_t> { 1, 2 },
                std::vector<std::uint32_t> { 0, 1, 3, 2 },
                std::vector<std::uint32_t> { 4, 2 },
        };
        cgp_feedforward n4(config4);

        n4.input(std::vector<float> { 2.2f, 1.0f, 3.2f });
        auto o7 = n4.get_outputs();
        EXPECT_FLOAT_EQ(o7[0], 3.84f);
        EXPECT_FLOAT_EQ(o7[1], 3.2f);

        cgp_feedforward_config config5 {
                3, 2,
                std::make_pair(2, 2),
                std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
                std::vector<std::uint32_t> { 1, 2, 3, 0 },
                std::vector<std::uint32_t> { 0, 2, 0, 1, 3, 4, 4, 2 },
                std::vector<std::uint32_t> { 0, 6 },
        };
        cgp_feedforward n5(config5);

        n5.input(std::vector<float> { 2.2f, 1.0f, 3.2f });
        auto o8 = n5.get_outputs();
        EXPECT_FLOAT_EQ(o8[0], 2.2);
        EXPECT_FLOAT_EQ(o8[1], 5.4);

        cgp_feedforward_config config6 {
                3, 2,
                std::make_pair(2, 2),
                std::vector<std::function<float(const std::vector<float>& args)>> { add, sub, mul, div },
                std::vector<std::uint32_t> { 1, 2, 3, 0 },
                std::vector<std::uint32_t> { 0, 2, 0, 1, 3, 4, 4, 2 },
                std::vector<std::uint32_t> { 5, 6 },
        };
        cgp_feedforward n6(config6);

        n6.input(std::vector<float> { 2.2f, 1.0f, 3.2f });
        auto o9 = n6.get_outputs();
        EXPECT_FLOAT_EQ(o9[0], -1.0f / 2.2f);
        EXPECT_FLOAT_EQ(o9[1], 5.4f);
    }

    TEST(CLASS_TEST, DEVNETWORK) {
        network_config config;
        config.input_num = 2;
        config.output_num = 1;
        config.node = std::vector<node_t> {
                { 0u, 0.5f },
                { 0u, 0.5f },
                { 0u, 0.5f },
                { 0u, 0.5f },
                { 0u, 0.5f },
                { 0u, 0.5f },
        };
        config.conn = std::vector<conn_t> {
                { 0, 1, 0.5f },
                { 1, 2, 0.5f },
                { 2, 3, 0.5f },
                { 3, 4, 0.5f },
                { 4, 5, 0.5f },
                { 4, 2, 0.5f },
                { 1, 4, 0.5f },
        };
        devnetwork n(config);
        for(auto i = 0; i < 100; i++) {
            n.input(std::vector<float> { 1.0f, 1.0f });
            std::cout << n.get_outputs()[0] << std::endl;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


