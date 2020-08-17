//
// Created by hungr on 2020/08/16.
//
#include "feedforward.h"

feedforward::feedforward(const network_config &config)
    : node_outputs(config.input_num + config.output_num + config.node.size()),
    config(config),
    outputs(config.output_num) {

}

void feedforward::input(const std::vector<float> &inputs) {
    std::fill(node_outputs.begin(), node_outputs.end(), 0);
    std::copy(inputs.begin(), inputs.end(), node_outputs.begin());
    std::sort(config.conn.begin(), config.conn.end(), [](auto&& p1, auto&& p2) { return std::get<0>(p1) < std::get<0>(p2); });
    for(auto&& c : config.conn) {
        std::uint32_t fid = std::get<0>(config.node[std::get<0>(c)]);
        float bias = std::get<1>(config.node[std::get<0>(c)]);
        node_outputs[std::get<1>(c)] += config.f[fid](node_outputs[std::get<0>(c)] + bias) * std::get<2>(c);
    }
    for(auto i = 0; i < config.output_num; i++) {
        std::uint32_t fid = std::get<0>(config.node[i + config.input_num]);
        float bias = std::get<1>(config.node[i + config.input_num]);
        outputs[i] = config.f[fid](node_outputs[config.input_num + i] + bias);
    }
}

const std::vector<float> &feedforward::get_outputs() const {
    return outputs;
}
