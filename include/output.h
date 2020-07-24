//
// Created by hungr on 2020/07/24.
//

#ifndef NETWORK_OUTPUT_H
#define NETWORK_OUTPUT_H

#include "circuitable.h"

class output :
        public circuitable
{
public:
    output() = default;
    void receive(float value, input_type type) override ;
    void send(float value) override ;
    void add_receiver(std::weak_ptr<circuitable> target) override ;
    void update() override ;
    double get_value() const;
private:
    float value;
};

#endif //NETWORK_OUTPUT_H
