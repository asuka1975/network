//
// Created by hungr on 2020/07/24.
//
#include "output.h"

void output::receive(float value, input_type type) {
    this->value = value;
}

void output::send(float value) {}
void output::add_receiver(std::weak_ptr<circuitable> target) {}
void output::update() {}

double output::get_value() const {
    return value;
}