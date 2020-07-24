//
// Created by hungr on 2020/07/24.
//
#include "synapse.h"

synapse::synapse(std::weak_ptr<circuitable> target, float weight) : receiver(target), weight(weight)
{
    weight_update = [](auto v, auto w) -> auto { return w; };
}

void synapse::receive(float value, input_type type) {
    switch (type) {
        case NEURON:
            send(value);
            break;
        case SYNAPSE:
            send(value);
            break;
    }
}

void synapse::send(float value) {
    if(auto r = receiver.lock()) {
        r->receive(value * weight, SYNAPSE);
        weight = weight_update(value, weight);
    }
}

void synapse::add_receiver(std::weak_ptr<circuitable> target) {
    receiver = target;
}

void synapse::update() {}