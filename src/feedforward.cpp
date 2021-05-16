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
    std::sort(config.conn.begin(), config.conn.end(), [](auto&& p1, auto&& p2) { return p1.in < p2.in; });
    for(auto&& c : config.conn) {
        std::uint32_t fid = config.node[c.in].fun_id;
        float bias = config.node[c.in].bias;
        node_outputs[c.out] += config.f[fid](node_outputs[c.in] + bias) * c.weight;
    }
    for(auto i = 0; i < config.output_num; i++) {
        std::uint32_t fid = config.node[i + config.input_num].fun_id;
        float bias = config.node[i + config.input_num].bias;
        outputs[i] = config.f[fid](node_outputs[config.input_num + i] + bias);
    }
}

const std::vector<float> &feedforward::get_outputs() const {
    return outputs;
}

std::size_t feedforward::size() const noexcept {
    return config.conn.size();
}
