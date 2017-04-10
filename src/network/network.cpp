#include "network.h"
#include <stdexcept>
#include "synapse/synapse.h"

Network::Network(int input_count, int hidden_count, int output_count)
{
    if((input_count > 0) && (hidden_count > 0) && (output_count > 0))
    {
        add_neurons_to_layer(input_layer, input_count);
        add_neurons_to_layer(hidden_layer, hidden_count);
        add_neurons_to_layer(output_layer, output_count);
        connect_layers(input_layer, hidden_layer);
        connect_layers(hidden_layer, output_layer);
        total_error = 0.0;
    } else
    {
        throw std::invalid_argument( "Network requires layers to be larger than 0" );
    }
}

/* To test this, give it a list and int, and then get the size of list */
void Network::add_neurons_to_layer(std::vector<Neuron>& layer, int neuron_count)
{
    for(int i=0; i<neuron_count; i++)
    {
        Neuron neuron;
        layer.emplace_back(neuron);
    }
}

void Network::connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer)
{
    for(auto& from_neuron: from_layer)
    {
        for(auto& to_neuron: to_layer)
        {
            Synapse new_synapse(from_neuron, to_neuron);
            Synapse& added_synapse = to_neuron.add_incoming_synapse(new_synapse);
            from_neuron.add_outgoing_synapse(added_synapse);
        }
    }
}

