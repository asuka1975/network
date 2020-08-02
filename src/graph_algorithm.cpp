//
// Created by hungr on 2020/07/30.
//
#include "graph_algorithm.h"
#include <algorithm>
#include <list>


bool is_acyclic(std::uint32_t node_count, const std::vector<std::pair<std::uint32_t, std::uint32_t>>& connection_rule) {
    std::list<std::uint32_t> sort_result;
    std::set<std::uint32_t> source;

    while(!source.empty()) {

    }
    return false;
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