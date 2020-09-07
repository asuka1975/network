//
// Created by hungr on 2020/08/29.
//
#include "devnetwork.h"

#include <random>

devnetwork::devnetwork(const network_config &config) :
    output(config.output_num), node_output(config.node.size()), nodes(config.node.size()), conns(config.conn.size()), config(config) {
    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::normal_distribution<float> dist(0.0f, 1.0f);// for initialization of position(TODO consider position initialization)
    for(auto i = 0; i < nodes.size(); i++) {
        std::get<0>(std::get<0>(nodes[i])) = dist(mt);
        std::get<1>(std::get<0>(nodes[i])) = dist(mt);
        std::get<1>(nodes[i]) = std::get<1>(config.node[i]);
        std::get<2>(nodes[i]) = 0.5f; // sample value
    }
    for(auto i = 0; i < conns.size(); i++) {
        std::get<0>(std::get<0>(conns[i])) = dist(mt);
        std::get<1>(std::get<0>(conns[i])) = dist(mt);
        std::get<1>(conns[i]) = std::get<2>(config.conn[i]);
        std::get<2>(conns[i]) = std::get<0>(config.conn[i]);
        std::get<3>(conns[i]) = std::get<1>(config.conn[i]);
    }
    neighbors_num = 0;
    hebb = std::make_tuple(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    auto empty_ret = std::make_tuple(false, std::make_tuple(0.0f, 0.0f), 0.0f);
    creator = [empty_ret](auto, auto) { return std::make_pair(empty_ret, empty_ret); };
    deleter = [](auto, auto, auto, auto) { return false; };
}

void devnetwork::input(const std::vector<float> &inputs) {
    std::vector<float> tmp(node_output.size());
    std::copy(inputs.begin(), inputs.end(), node_output.begin());//TODO consider input behavior
    for(auto& c : conns) {
        float o = node_output[std::get<2>(c)] * std::get<1>(c);
        tmp[std::get<3>(c)] += o;
    }
    // update weight
    for(auto& c : conns) {
        float o1 = node_output[std::get<2>(c)];
        float o2 = tmp[std::get<3>(c)];
        std::get<1>(c) += std::get<0>(hebb) * (std::get<1>(hebb) * o1 * o2 +
                std::get<2>(hebb) * o1 + std::get<3>(hebb) * o2 + std::get<4>(hebb));
    }
    // update energy
    float a = 1.0f;
    for(auto i = 0; i < tmp.size(); i++) {
        //
        float e = std::get<2>(nodes[i]);
        float x = (std::log(e) - std::log(1 - e)) / a;
        x = std::isinf(x) ? (std::signbit(x) ? std::numeric_limits<float>::lowest() : std::numeric_limits<float>::max()) : x;
        x += tmp[i];
        std::get<2>(nodes[i]) = 1.0f / (1.0f + std::exp(-a * x));
    }
    node_output = tmp;
    std::copy(node_output.begin() + config.input_num, node_output.begin() + config.input_num + config.output_num, output.begin());
    develop();
}

const std::vector<float> &devnetwork::get_outputs() const {
    return output;
}

std::size_t devnetwork::size() const noexcept {
    return conns.size();
}

void devnetwork::develop() {
    auto c = 0;
    for(auto i = 0; i < nodes.size(); i++) {
        std::vector<std::ptrdiff_t> idxes(nodes.size());
        std::iota(idxes.begin(), idxes.end(), 0);
        std::sort(idxes.begin(), idxes.end(), [&nodes=nodes, k=i](auto i, auto j) {
            float xk = std::get<0>(std::get<0>(nodes[k]));
            float yk = std::get<1>(std::get<0>(nodes[k]));
            float xi = std::get<0>(std::get<0>(nodes[i]));
            float yi = std::get<1>(std::get<0>(nodes[i]));
            float xj = std::get<0>(std::get<0>(nodes[j]));
            float yj = std::get<1>(std::get<0>(nodes[j]));
            float d1 = (xk - xi) * (xk - xi) + (yk - yi) * (yk - yi);
            float d2 = (xk - xj) * (xk - xj) + (yk - yj) * (yk - yj);
            return d1 < d2;
        });
        std::vector<neuron_t> n(neighbors_num);
        for(auto j = 0; j < neighbors_num; j++) {
            n[j] = nodes[idxes[j]];
        }
        int count = 0;
        synapse_t s = std::make_tuple(std::make_tuple(0.0f, 0.0f), 0.0f);
        for(auto& conn : conns) {
            if(std::get<3>(conn) == i) {
                std::get<0>(std::get<0>(s)) += std::get<0>(std::get<0>(conn));
                std::get<1>(std::get<0>(s)) += std::get<1>(std::get<0>(conn));
                std::get<1>(s) += std::get<1>(conn);
                count++;
            }
        }
        if(count != 0) {
            std::get<0>(std::get<0>(s)) /= count;
            std::get<1>(std::get<0>(s)) /= count;
            std::get<1>(s) /= count;
        }
        auto [nc, sc] = creator(n, s);

        for(auto i = 0; i < conns.size(); i++) {
            if(deleter(nodes[std::get<2>(conns[i])], nodes[std::get<3>(conns[i])], std::get<0>(conns[i]), std::get<1>(conns[i]))) {
                conns.erase(conns.begin() + i);
                i--;
            }
        }
        if(std::get<0>(nc)) {
            nodes.emplace_back(std::get<1>(nc), std::get<2>(nc), 0.5f);
            c++;
        }
        if(std::get<0>(sc)) {
            auto iter = std::min_element(nodes.begin(), nodes.end(), [&sc=sc] (auto n1, auto n2) -> bool {
                float xs = std::get<0>(std::get<1>(sc));
                float ys = std::get<1>(std::get<1>(sc));
                float x1 = std::get<0>(std::get<0>(n1));
                float y1 = std::get<1>(std::get<0>(n1));
                float x2 = std::get<0>(std::get<0>(n2));
                float y2 = std::get<1>(std::get<0>(n2));
                return (x1 - xs) * (x1 - xs) + (y1 - ys) * (y1 - ys) < (x2 - xs) * (x2 - xs) + (y2 - ys) * (y2 - ys);
            });
            conns.emplace_back(std::get<1>(sc), std::get<2>(sc), nodes.size() - 1, iter - nodes.begin());
        }
    }
    node_output.resize(node_output.size() + c);
}
