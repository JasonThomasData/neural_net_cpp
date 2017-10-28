#include "synapse.h"
#include "../neuron/neuron.h"
#include <iostream>


Synapse::Synapse(Neuron& from_neuron, Neuron& to_neuron)
    : from_neuron(from_neuron), to_neuron(to_neuron){}

double Synapse::get_from_neuron_weighted_outgoing_value()
{
    double weighted_value = from_neuron.outgoing_value * weight;
    return weighted_value;
}

double Synapse::get_weight()
{
    return weight;
}

void Synapse::set_weight(double new_weight)
{
    weight = new_weight;
}

Neuron& Synapse::get_from_neuron()
{
    return from_neuron;
}

Neuron& Synapse::get_to_neuron()
{
    return to_neuron;
}
