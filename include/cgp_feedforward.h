//
// Created by hungr on 2020/08/06.
//

#ifndef NETWORK_CGP_FEEDFORWARD_H
#define NETWORK_CGP_FEEDFORWARD_H

#include <functional>
#include <vector>


struct cgp_feedforward_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::pair<std::uint32_t, std::uint32_t> network_size;
    std::vector<std::function<float(const std::vector<float>& args)>> f;
    std::vector<std::uint32_t> node;
    std::vector<std::uint32_t> conn;
    std::vector<std::uint32_t> output;
};

class cgp_feedforward {
public:
    explicit cgp_feedforward(const cgp_feedforward_config& config);
    void input(const std::vector<float>& inputs);
    [[nodiscard]] const std::vector<float>& get_outputs() const;
private:
    cgp_feedforward_config config;
    std::vector<float> outputs;
    std::vector<float> node_outputs;
};

#endif //NETWORK_CGP_FEEDFORWARD_H
