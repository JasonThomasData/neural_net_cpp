#include "classifier.h"
#include "feed_forward.h"
#include "../network/network.h"
#include "../neuron/neuron.h"
#include <stdexcept>

Classifier::Classifier(Network& network_ref)
    :network(network_ref){}

/* If this doesn't meet the condition of being the same size, we should log the result. */

void Classifier::set_input_values(std::vector<double> new_input_values)
{
    int input_layer_size = network.input_layer.size();
    int new_input_size = new_input_values.size();

    if(input_layer_size == new_input_size)
    {
        for(int i=0; i< input_layer_size; i++)
        {
            Neuron& neuron = network.input_layer.at(i);
            neuron.outgoing_value = new_input_values.at(i);
        }
    } else
    {
        throw std::invalid_argument( "Network requires input layer and new values to be the same length" );
    }
}

void Classifier::classify()
{
    FeedForward::update_layer(network.hidden_layer);
    FeedForward::update_layer(network.output_layer);
}
