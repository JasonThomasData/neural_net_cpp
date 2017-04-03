#include "soma.h"
#include "synapse.h"
#include <cmath>
#include <iostream>

Soma::Soma(){}

float Soma::add_incoming_values()
{
    float incoming_values = 0;

    for(auto& synapse: all_synapses)
    {
        incoming_values += synapse.get_weighted_incoming_value();
    }

    return incoming_values;
}

float Soma::activate(float incoming_values)
{
    /* This is a logistic function | 1/(1 + E^-X) | where E is Euler's number and X is the
     * incoming_values
     * The output will always range between 0 and 1, and usually closer to 0.5
     * Source - https://en.wikipedia.org/wiki/Logistic_function
     */
    float euler_number = 2.71828;
    float incoming_values_neg = incoming_values *= -1;
    float activation_result = 1/(1 + pow(euler_number, incoming_values_neg));

    return activation_result;
}

