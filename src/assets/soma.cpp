#include "soma.h"
#include "synapse.h"

Soma::Soma(float init_threshold)
{
    threshold = init_threshold;
}

float Soma::add_incoming_values()
{
    int number_synapses = all_synapses.size();
    float incoming_values = 0;

    for(int i=0; i<number_synapses; i++)
    {
        incoming_values += all_synapses.at(i).get_weighted_incoming_value();
    }

    return incoming_values;
}

/* For now, this is merely a stepper function, binary. Might extend this to allow for gradient. */
float Soma::activate(float incoming_values)
{
    float activation_result;

    if (incoming_values < threshold)
    {
        activation_result = 0.0;
    } else
    {
        activation_result = 1.0;
    }

    return activation_result;
}

