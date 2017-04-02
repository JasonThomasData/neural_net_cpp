#include "synapse.h"
#include "neuron.h"

Synapse::Synapse(Neuron& from_neuron, Neuron& to_neuron)
    : from_neuron(from_neuron), to_neuron(to_neuron){}

float Synapse::get_weighted_incoming_value()
{
    float weighted_value = from_neuron.get_output_value() * weight;
    return weighted_value;
}

void Synapse::update_weight(float change_value)
{
    weight -= change_value;
}
