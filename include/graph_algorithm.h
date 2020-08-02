//
// Created by hungr on 2020/07/30.
//

#ifndef NETWORK_GRAPH_ALGORITHM_H
#define NETWORK_GRAPH_ALGORITHM_H

#include <cstdint>
#include <set>
#include <vector>

void find_source(std::uint32_t node_count,
                 const std::vector<std::pair<std::uint32_t, std::uint32_t>>& connection_rule,
                 std::set<std::uint32_t>& source);
bool is_acyclic(std::uint32_t node_count, const std::vector<std::pair<std::uint32_t, std::uint32_t>>& connection_rule);

#endif //NETWORK_GRAPH_ALGORITHM_H
