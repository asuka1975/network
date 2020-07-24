//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_CIRCUITABLE_H
#define NETWORK_CIRCUITABLE_H

#include <memory>

enum input_type {
    NEURON,
    SYNAPSE
};

class circuitable {
public:
    virtual void receive(float value, input_type type) = 0;
    virtual void send(float value) = 0;
    virtual void add_receiver(std::weak_ptr<circuitable> target) = 0;
    virtual void update() = 0;
    virtual ~circuitable() = default;
};

#endif //NETWORK_CIRCUITABLE_H
