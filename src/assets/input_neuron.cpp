#include "input_neuron.h"

InputNeuron::InputNeuron(){} 

float InputNeuron::get_outgoing_value()
{
    return outgoing_value;
}

/* This function should never be called, because an InputNeuron's only purpose is to have an output.
 */
float InputNeuron::get_incoming_values()
{
    return 0.0;
}
