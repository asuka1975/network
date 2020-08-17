//
// Created by hungr on 2020/07/24.
//
#include "network.h"

#include "neuron.h"
#include "synapse.h"

deprecated::network::network(const network_config &config) {
    for(auto i = 0; i < config.node_count; i++) {
        neurons.push_back(std::make_shared<neuron>(config.bias[i], config.activations[i]));
    }
    for(auto i = 0; i < config.connection_count; i++) {
        synapses.push_back(std::make_shared<synapse>(neurons[config.connection_rule[i].second], config.weight[i]));
        neurons[config.connection_rule[i].first]->add_receiver(synapses.back());
    }
    for(auto i = config.input_count; i< config.input_count + config.output_count; i++) {
        outputs.push_back(std::make_shared<output>());
        neurons[i]->add_receiver(outputs.back());
    }
}

void deprecated::network::input(const std::vector<float> &inputs) {
    for(auto i = 0; i < inputs.size(); i++) {
        neurons[i]->receive(inputs[i], NEURON);
    }
    for(auto& n : neurons) {
        n->send(0.0);
    }
    for(auto& n : neurons) {
        n->update();
    }
}

std::vector<float> deprecated::network::get_outputs() const {
    std::vector<float> v;
    for(const auto& o : outputs) {
        v.push_back(o->get_value());
    }
    return v;
}