//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_NEURON_H
#define NETWORK_NEURON_H

#include <functional>
#include <memory>
#include <vector>
#include "circuitable.h"

class neuron :
        public circuitable
{
public:
    neuron(float bias, std::function<float(float)> activation);
    void receive(float value, input_type type) override ;
    void send(float value) override ;
    void add_receiver(std::weak_ptr<circuitable> target) override ;
    void update() override ;
private:
    std::vector<std::weak_ptr<circuitable>> receivers;
    std::function<float(float)> activation_function;
    float bias;
    float input_pool;
    float output;
    int count;
};

#endif //NETWORK_NEURON_H
