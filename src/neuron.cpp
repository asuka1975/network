//
// Created by hungr on 2020/07/24.
//
#include "neuron.h"

neuron::neuron(float bias, std::function<float (float)> activation):
    bias(bias), output(0), activation_function(activation)
{
    static int i = 0;
    count = i;
    i++;
}

void neuron::receive(float value, input_type type) {
    input_pool += value;
}

void neuron::send(float value) {
    float v = output;
    output = 0;
    for(auto wr : receivers) {
        if(auto r = wr.lock()) {
            r->receive(v, NEURON);
        }
    }
}

void neuron::add_receiver(std::weak_ptr<circuitable> target) {
    receivers.push_back(target);
}

void neuron::update() {
    output = activation_function(input_pool);
    input_pool = 0;
}