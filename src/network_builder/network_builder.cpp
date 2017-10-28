#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>

#include "../network/network.h"
#include "../neuron/neuron.h"
#include "../synapse/synapse.h"
#include "../synapse/i_synapse.h"
#include "network_builder.h"

NetworkBuilder::NetworkBuilder(){}

Network NetworkBuilder::build_network(std::vector<int> layer_counts)
{
    int input_count = layer_counts.at(0);
    int hidden_count = layer_counts.at(1);
    int output_count = layer_counts.at(2);

    if((input_count > 0) && (hidden_count > 0) && (output_count > 0))
    {
        std::vector<Neuron> input_layer = create_layer(input_count);
        std::vector<Neuron> hidden_layer = create_layer(hidden_count);
        std::vector<Neuron> output_layer = create_layer(output_count);
        connect_layers(input_layer, hidden_layer);
        connect_layers(hidden_layer, output_layer);

        randomise_synapse_weights(input_layer);
        randomise_synapse_weights(hidden_layer);

        Network network(std::move(input_layer),
                        std::move(hidden_layer),
                        std::move(output_layer));
        return network;

    } else
    {
        throw std::invalid_argument( "Network requires layers to be larger than 0" );
    }
}

std::vector<Neuron> NetworkBuilder::create_layer(int neuron_count)
{
    std::vector<Neuron> layer;
    for(int i=0; i<neuron_count; i++)
    {
        Neuron neuron;
        layer.emplace_back(std::move(neuron));
    }
    return layer;
}

// With interface, the INeuron already has functions for adding data members, so does ISynapse
// NOTE ! This function does too much, split this up
// The task of adding synapses should be separate from randomising them
void NetworkBuilder::connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer)
{
    for(auto& from_neuron: from_layer)
    {
        for(auto& to_neuron: to_layer)
        {
            std::unique_ptr<ISynapse> new_synapse = std::make_unique<Synapse>(from_neuron, to_neuron);
            std::reference_wrapper<ISynapse> added_synapse = to_neuron.add_incoming_synapse(std::move(new_synapse));
            from_neuron.add_outgoing_synapse(added_synapse);
        }
    }
}

void NetworkBuilder::randomise_synapse_weights(std::vector<Neuron>& owning_layer)
{
    srand(time(NULL));
    int seed_range = 20;
    for(auto& owning_neuron: owning_layer)
    {
        for(auto& synapse: owning_neuron.outgoing_synapses)
        {
            double random_number = rand() % seed_range;
            double weight = random_number / seed_range;
            synapse.get().set_weight(weight);
        }
    }
}
