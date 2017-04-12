#include "synapse.h"
#include "../neuron/neuron.h"
#include <iostream>


Synapse::Synapse(Neuron& from_neuron, Neuron& to_neuron, double weight)
    : from_neuron(from_neuron), to_neuron(to_neuron), weight(weight){}

double Synapse::get_from_neuron_weighted_outgoing_value()
{
    double weighted_value = from_neuron.outgoing_value * weight;
    return weighted_value;
}

