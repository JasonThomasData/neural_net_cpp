#include "input.h"

InputNeuron::InputNeuron(){} 

float InputNeuron::get_outgoing_value()
{
    return outgoing_value;
}

/* This should never be called */
float InputNeuron::get_incoming_values()
{
    return 0.0;
}
