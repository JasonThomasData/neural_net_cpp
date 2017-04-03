#include "synapse.h"
#include "neuron.h"

Neuron::Neuron(){}

void Neuron::add_synapse(Synapse& new_synapse)
{
    all_synapses.emplace_back(new_synapse);
}

void Neuron::set_output_value()
{
    float incoming_values = add_incoming_values();
    float activation_result = activate(incoming_values);
    output_value = activation_result;
}

float Neuron::get_output_value()
{
    return output_value;
}
