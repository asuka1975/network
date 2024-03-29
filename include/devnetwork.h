//
// Created by hungr on 2020/08/29.
//

#ifndef NETWORK_DEVNETWORK_H
#define NETWORK_DEVNETWORK_H

#include "network.h"

struct devnet_extensions {
    inline static bool enable_evolving_neurocomponents_position = false;
    inline static bool enable_activation_function = false;
    inline static bool enable_input_step = false;
};

class devnetwork {
public:
    explicit devnetwork(const network_config& config);
    void initialize();
    void input(const std::vector<float>& inputs);
    [[nodiscard]] const std::vector<float>& get_outputs() const;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] std::size_t node_num() const noexcept ;
    using position_t = std::tuple<float, float>;
    using neuron_t = std::tuple<position_t, float, float>; // position, bias, energy
    using synapse_t = std::tuple<position_t, float>;
    using neuron_ret_t = std::tuple<bool, position_t, float>;
    using synapse_ret_t = std::tuple<bool, position_t, float>;
    std::function<std::pair<neuron_ret_t, synapse_ret_t>(const std::vector<neuron_t>&, synapse_t, std::size_t)> creator;
    std::function<bool(neuron_t, neuron_t, position_t, float, std::size_t)> deleter;
    std::tuple<float, float, float, float, float> hebb;//k(A*oi*oj + B*oi + C*oj + D)
    std::function<std::tuple<float, float>()> position_initializer;
    int neighbors_num;
    [[nodiscard]] const std::vector<neuron_t>& get_nodes() const noexcept;
    [[nodiscard]] const std::vector<std::tuple<position_t, float, std::uint32_t, std::uint32_t>>& get_conns() const noexcept ;
    static std::size_t num_creator_inputs(int neighbor_num);
    static std::size_t num_deleter_inputs();
private:
    void develop();
    network_config config;
    std::vector<float> output;
    std::vector<float> node_output;
    std::vector<neuron_t> nodes;
    std::vector<std::tuple<position_t, float, std::uint32_t, std::uint32_t>> conns; // position, weight, in, out
    std::size_t counter;
};

#endif //NETWORK_DEVNETWORK_H
