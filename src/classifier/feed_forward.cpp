#include "feed_forward.h"
#include "../synapse/i_synapse.h"
#include "../neuron/neuron.h"
#include <cmath>
#include <vector>
#include <memory>

//FeedForward::FeedForward(){}

double FeedForward::calculate_incoming_values(std::vector<std::unique_ptr<ISynapse>>& incoming_synapses)
{
    double incoming_values = 0;
    for(auto& synapse: incoming_synapses)
    {
        incoming_values += synapse->get_from_neuron_weighted_outgoing_value();
    }
    return incoming_values;
}

/* This is a logistic function | 1/(1 + E^-X) | where E is Euler's number and X is the
 * incoming_values
 * The output will always range between 0 and 1, and usually closer to 0.5
 * Source - https://en.wikipedia.org/wiki/Logistic_function
 */
double FeedForward::activate(double incoming_values)
{
    float euler_number = 2.71828;
    double incoming_values_neg = -incoming_values;
    double activation_result = 1/(1 + pow(euler_number, incoming_values_neg));
    return activation_result;
}

void FeedForward::update_neuron(Neuron& neuron)
{
    neuron.incoming_values = calculate_incoming_values(neuron.incoming_synapses);
    neuron.outgoing_value = activate(neuron.incoming_values);
}

void FeedForward::update_layer(std::vector<Neuron>& layer)
{
    for(auto& neuron: layer)
    {
        update_neuron(neuron);
    }
}

