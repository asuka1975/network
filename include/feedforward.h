//
// Created by hungr on 2020/08/16.
//

#ifndef NETWORK_FEEDFORWARD_H
#define NETWORK_FEEDFORWARD_H

#include <functional>
#include <vector>

struct feedforward_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::vector<std::function<float(float)>> f;
    std::vector<std::uint32_t> node;
    std::vector<float> bias;
    std::vector<std::tuple<std::uint32_t, std::uint32_t, float>> conn;
    std::vector<std::uint32_t> output;
};

class feedforward {
public:
    explicit feedforward(const feedforward_config& config);
    void input(const std::vector<float>& inputs);
    [[nodiscard]] const std::vector<float>& get_outputs() const;
private:
    feedforward_config config;
    std::vector<float> outputs;
    std::vector<float> node_outputs;
};

#endif //NETWORK_FEEDFORWARD_H
