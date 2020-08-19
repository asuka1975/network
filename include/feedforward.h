//
// Created by hungr on 2020/08/16.
//

#ifndef NETWORK_FEEDFORWARD_H
#define NETWORK_FEEDFORWARD_H

#include <functional>
#include <vector>
#include "network.h"

struct feedforward_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::vector<std::function<float(float)>> f;
    std::vector<std::tuple<std::uint32_t, float>> node;
    std::vector<std::tuple<std::uint32_t, std::uint32_t, float>> conn;
};

class feedforward : public network {
public:
    explicit feedforward(const network_config& config);
    void input(const std::vector<float>& inputs) override;
    [[nodiscard]] const std::vector<float>& get_outputs() const override;
    std::size_t size() const noexcept override;
private:
    network_config config;
    std::vector<float> outputs;
    std::vector<float> node_outputs;
};

#endif //NETWORK_FEEDFORWARD_H
