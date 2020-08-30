//
// Created by hungr on 2020/08/29.
//

#ifndef NETWORK_DEVNETWORK_H
#define NETWORK_DEVNETWORK_H

#include "network.h"

class devnetwork {
public:
    explicit devnetwork(const network_config& config);
    void input(const std::vector<float>& inputs);
    [[nodiscard]] const std::vector<float>& get_outputs() const;
    std::size_t size() const noexcept;
    using position_t = std::tuple<float, float>;
    using neuron_t = std::tuple<position_t, float, float>;
    using synapse_t = std::tuple<position_t, float>;
    using neuron_ret_t = std::tuple<bool, position_t, float>;
    using synapse_ret_t = std::tuple<bool, position_t, float>;
    std::function<std::pair<neuron_ret_t, synapse_ret_t>(const std::vector<neuron_t>&, synapse_t)> creator;
    std::function<bool(neuron_t, neuron_t, position_t, float)> deleter;
private:
    network_config config;
};

#endif //NETWORK_DEVNETWORK_H