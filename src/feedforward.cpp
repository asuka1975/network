//
// Created by hungr on 2020/08/06.
//
#include "feedforward.h"

feedforward::feedforward(const feedforward_config &config)
    : node_outputs(config.input_num + config.network_size.first * config.network_size.second),
    config(config),
    outputs(config.output_num){

}

void feedforward::input(const std::vector<float> &inputs) {
    std::copy(inputs.begin(), inputs.end(), node_outputs.begin());
    auto arg_num = config.node.size() ? config.conn.size() / config.node.size() : 0;
    std::vector<float> args(arg_num);
    for(auto i = 0; i < config.node.size(); i++) {
        for(auto j = 0; j < arg_num; j++) {
            args[j] = node_outputs[config.conn[i * arg_num + j]];
        }
        node_outputs[i + inputs.size()] = config.f[config.node[i]](args);
    };
    auto j = 0;
    for(auto i : config.output) {
        outputs[j++] = node_outputs[i];
    }
}

const std::vector<float>& feedforward::get_outputs() const {
    return outputs;
}
