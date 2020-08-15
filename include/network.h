//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include <functional>
#include <memory>
#include <vector>
#include "circuitable.h"
#include "output.h"

struct network_config {
    int input_count;
    int output_count;
    int node_count;
    int connection_count;
    std::vector<float> bias;
    std::vector<float> weight;
    std::vector<std::pair<std::uint32_t, std::uint32_t>> connection_rule;
    std::vector<std::function<float(float)>> activations;
};

class network {
public:
    network() = default;
    network(const network_config& config);
    void input(const std::vector<float>& inputs);
    std::vector<float> get_outputs() const;
private:
    std::vector<std::shared_ptr<circuitable>> neurons;
    std::vector<std::shared_ptr<circuitable>> synapses;
    std::vector<std::shared_ptr<output>> outputs;
};

#endif //NETWORK_NETWORK_H
