#include <vector>
#include <iostream>
#include <string>
#include "writer.h"
#include "../network/network.h"
#include "../neuron/neuron.h"
#include "../synapse/synapse.h"

Writer::Writer(){}

/*
void Writer::process_neuron(Neuron& neuron, int layer_i&, int neuron_i,
                           std::string& text_to_dump)
{
    std::vector<Synapse> incoming_synapses = neuron.incoming_synapses;
    for(int neuron_i=0; neuron_i<neurons_in_layer; neuron_i++)
    {
        Neuron neuron& = layer.at(neuron_i)
        std::vector<Synapse> incoming_synapses = neuron.incoming_synapses;
        process_neuron(to_neuron.incoming_synapses, text_to_dump);
    }
}

void Writer::process_network_layer(std::vector<Neuron>& layer, int layer_i&,
                                   std::string& text_to_dump)
{
    int neurons_in_layer = layer.size();
    for(int neuron_i=0; neuron_i<neurons_in_layer; neuron_i++)
    {
        Neuron neuron& = layer.at(neuron_i)
        process_neuron(neuron, text_to_dump);
    }
}

void Writer::dump_network_data(Network& network)
{
    std::string text_to_write;

    std::vector<Neuron> hidden_layer = network.hidden_layer;
    int layer_i = 1;
    process_network_layer(hidden_layer, layer_i, text_to_write);

    std::vector<Neuron> output_layer = network.output_layer;
    int layer_i = 2;
    process_network_layer(output_layer, layer_i, text_to_write);
}
*/
