#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>

#include "network.h"
#include "synapse/synapse.h"
#include "synapse/i_synapse.h"

Network::Network(std::vector<int> layer_counts)
{
    int input_count = layer_counts.at(0);
    int hidden_count = layer_counts.at(1);
    int output_count = layer_counts.at(2);

    if((input_count > 0) && (hidden_count > 0) && (output_count > 0))
    {
        add_neurons_to_layer(input_layer, input_count);
        add_neurons_to_layer(hidden_layer, hidden_count);
        add_neurons_to_layer(output_layer, output_count);
        connect_layers(input_layer, hidden_layer);
        connect_layers(hidden_layer, output_layer);
        epoch_average_total_error = 0.0;
    } else
    {
        throw std::invalid_argument( "Network requires layers to be larger than 0" );
    }
}

void Network::add_neurons_to_layer(std::vector<Neuron>& layer, int neuron_count)
{
    for(int i=0; i<neuron_count; i++)
    {
        Neuron neuron;
        layer.emplace_back(std::move(neuron));
    }
}

// With interface, the INeuron already has functions for adding data members, so does ISynapse
// NOTE ! This function does too much, split this up
void Network::connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer)
{
    srand(time(NULL));
    int seed_range = 20;
    for(auto& from_neuron: from_layer)
    {
        for(auto& to_neuron: to_layer)
        {
            float random_sequence = rand() % seed_range;
            float weight = random_sequence / seed_range;
            std::unique_ptr<ISynapse> new_synapse = std::make_unique<Synapse>(from_neuron,
                                                                              to_neuron, weight);
            std::reference_wrapper<ISynapse> added_synapse = to_neuron.add_incoming_synapse(std::move(new_synapse));
            from_neuron.add_outgoing_synapse(added_synapse);
        }
    }
}
