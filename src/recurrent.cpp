//
// Created by hungr on 2020/08/18.
//
#include "recurrent.h"

recurrent::recurrent(const network_config &config)
        : node_outputs(config.input_num + config.output_num + config.node.size()),
          config(config),
          outputs(config.output_num)  {

}

void recurrent::input(const std::vector<float> &inputs) {
    std::vector<float> tmp(node_outputs.size());
    for(auto&& c : config.conn) {
        std::uint32_t fid = std::get<0>(config.node[std::get<0>(c)]);
        float bias = std::get<1>(config.node[std::get<0>(c)]);
        tmp[std::get<1>(c)] += config.f[fid](node_outputs[std::get<0>(c)] + bias) * std::get<2>(c);
    }
    std::copy(tmp.begin(), tmp.end(), node_outputs.begin());
    for(auto i = 0; i < config.output_num; i++) {
        std::uint32_t fid = std::get<0>(config.node[i + config.input_num]);
        float bias = std::get<1>(config.node[i + config.input_num]);
        outputs[i] = config.f[fid](node_outputs[config.input_num + i] + bias);
    }
}

const std::vector<float> &recurrent::get_outputs() const {
    return outputs;
}
