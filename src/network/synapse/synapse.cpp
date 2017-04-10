#include "synapse.h"
#include "../neuron/neuron.h"

Synapse::Synapse(Neuron& from_neuron, Neuron& to_neuron)
    : from_neuron(from_neuron), to_neuron(to_neuron){}

float Synapse::get_from_neuron_weighted_outgoing_value()
{
    float weighted_value = from_neuron.outgoing_value * weight;
    return weighted_value;
}

