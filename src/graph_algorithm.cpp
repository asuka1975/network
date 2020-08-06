//
// Created by hungr on 2020/07/30.
//
#include "graph_algorithm.h"
#include <algorithm>
#include <functional>
#include <list>


bool is_acyclic(std::uint32_t node_count, const std::vector<std::pair<std::uint32_t, std::uint32_t>>& connection_rule) {
    std::list<std::uint32_t> sort_result;
    std::set<std::uint32_t> source;
    find_source(node_count, connection_rule, source);

    using pair_compare = std::function<bool(
            std::pair<std::uint32_t, std::uint32_t>,
            std::pair<std::uint32_t, std::uint32_t>)>;
    std::set<std::pair<std::uint32_t, std::uint32_t>, pair_compare> G(connection_rule.begin(), connection_rule.end(),
            [node_count](auto a, auto b) -> bool { return (a.first * node_count + a.second) < (b.first * node_count + b.second); });
    while(!source.empty()) {
        std::uint32_t n;
        sort_result.push_back(n = source.extract(source.begin()).value());
        auto iter = std::find_if(G.begin(), G.end(), [n](auto&& a) {
            return a.first == n;
        });
        for(; iter != G.end() && iter->first == n; ) {
            auto&& p = *iter;
            auto&& m = p.second;
            iter = G.erase(iter);
            if(std::find_if(G.begin(), G.end(), [m](auto&& p) { return p.second == m; }) == G.end()) {
                source.insert(m);
            }
        }
    }
    return G.empty();
}

void find_source(std::uint32_t node_count,
                 const std::vector<std::pair<std::uint32_t, std::uint32_t>>& connection_rule,
                 std::set<std::uint32_t>& source) {
    for(auto n = 0; n < node_count; n++) {
        if(std::find_if(
                connection_rule.begin(),
                connection_rule.end(),
                [n](auto&& c) { return c.second == n; })
           == connection_rule.end()) {
            source.insert(n);
        }
    }
}