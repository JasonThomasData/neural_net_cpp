#include "synapse.h"
#include "../neuron/interface.h"

Synapse::Synapse(NeuronInterface& from_neuron, NeuronInterface& to_neuron)
    : from_neuron(from_neuron), to_neuron(to_neuron){}

float Synapse::get_to_neuron_incoming_values()
{
    float incoming_value = to_neuron.get_incoming_values();
    return incoming_value;
}

float Synapse::get_from_neuron_weighted_outgoing_value()
{
    float weighted_value = from_neuron.get_outgoing_value() * weight;
    return weighted_value;
}

float Synapse::get_from_neuron_outgoing_value()
{
    float outgoing_value = from_neuron.get_outgoing_value();
    return outgoing_value;
}
