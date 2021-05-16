//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_NETWORK_H
#define NETWORK_NETWORK_H

#include <functional>
#include <memory>
#include <vector>
#include <any>
#include "circuitable.h"
#include "output.h"

namespace deprecated {
    struct network_config {
        int input_count;
        int output_count;
        int node_count;
        int connection_count;
        std::vector<float> bias;
        std::vector<float> weight;
        std::vector<std::pair<std::uint32_t, std::uint32_t>> connection_rule;
        std::vector<std::function<float(float)>> activations;
    };

    class network {
    public:
        network() = default;

        network(const network_config &config);

        void input(const std::vector<float> &inputs);

        std::vector<float> get_outputs() const;

    private:
        std::vector<std::shared_ptr<circuitable>> neurons;
        std::vector<std::shared_ptr<circuitable>> synapses;
        std::vector<std::shared_ptr<output>> outputs;
    };
}

struct node_t {
    std::uint32_t fun_id;
    float bias;
    std::any extra;
};

struct conn_t {
    std::uint32_t in;
    std::uint32_t out;
    float weight;
    std::any extra;
};

struct network_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::vector<std::function<float(float)>> f;
    std::vector<node_t> node;
    std::vector<conn_t> conn;
};

class network {
public:
    virtual void input(const std::vector<float>& inputs) = 0;
    [[nodiscard]] virtual const std::vector<float>& get_outputs() const = 0;
    virtual std::size_t size() const noexcept = 0;
    virtual ~network() = default;
};
#endif //NETWORK_NETWORK_H
