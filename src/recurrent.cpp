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
        std::uint32_t fid = config.node[c.in].fun_id;
        float bias = config.node[c.in].bias;
        tmp[c.out] += config.f[fid](node_outputs[c.in] + bias) * c.weight;
    }
    std::copy(tmp.begin(), tmp.end(), node_outputs.begin());
    for(auto i = 0; i < config.output_num; i++) {
        std::uint32_t fid = config.node[i + config.input_num].fun_id;
        float bias = config.node[i + config.input_num].bias;
        outputs[i] = config.f[fid](node_outputs[config.input_num + i] + bias);
    }
}

const std::vector<float> &recurrent::get_outputs() const {
    return outputs;
}

std::size_t recurrent::size() const noexcept {
    return config.conn.size();
}
