//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_SYNAPSE_H
#define NETWORK_SYNAPSE_H

#include <functional>
#include <memory>
#include "circuitable.h"

class synapse :
        public circuitable
{
public:
    synapse(std::weak_ptr<circuitable> target, float weight);
    void receive(float value, input_type type) override ;
    void send(float value) override ;
    void add_receiver(std::weak_ptr<circuitable> target) override ;
    void update() override ;
    std::function<float(float, float)> weight_update;
private:
    std::weak_ptr<circuitable> receiver;
    float weight;
};

#endif //NETWORK_SYNAPSE_H
