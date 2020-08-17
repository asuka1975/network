//
// Created by hungr on 2020/08/18.
//

#ifndef NETWORK_RECURRENT_H
#define NETWORK_RECURRENT_H

#include "network.h"

class recurrent : public network {
    explicit recurrent(const network_config& config);
    void input(const std::vector<float>& inputs) override;
    [[nodiscard]] const std::vector<float>& get_outputs() const override;
private:
    network_config config;
    std::vector<float> outputs;
    std::vector<float> node_outputs;
};

#endif //NETWORK_RECURRENT_H
