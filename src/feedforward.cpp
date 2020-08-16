//
// Created by hungr on 2020/08/16.
//
#include "feedforward.h"

feedforward::feedforward(const feedforward_config &config)
    : node_outputs(config.input_num + config.output_num + config.node.size()),
    config(config),
    outputs(config.output_num) {

}

void feedforward::input(const std::vector<float> &inputs) {
    std::fill(node_outputs.begin(), node_outputs.end(), 0);
    std::copy(inputs.begin(), inputs.end(), node_outputs.begin());
    std::sort(config.conn.begin(), config.conn.end(), [](auto&& p1, auto&& p2) { return p1.first < p2.first; });
    for(auto&& c : config.conn) {
        node_outputs[std::get<1>(c)] += config.f[config.node[std::get<0>(c)]](node_outputs[std::get<0>(c)] + config.bias[std::get<0>(c)]) * std::get<2>(c);
    }
    for(auto i = 0; i < config.output_num; i++) {
        outputs[i] = config.f[config.output[i]](node_outputs[config.input_num + i]);
    }
}

const std::vector<float> &feedforward::get_outputs() const {
    return outputs;
}
