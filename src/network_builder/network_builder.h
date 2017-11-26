#ifndef NetworkBuilder_h
#define NetworkBuilder_h

#include <vector>

#include "../network/network.h"

//Although this could be a namespace, this is a convenient way to hide functions for now
class Neuron;
class SynapseData;
class NetworkData;

class NetworkBuilder
{
    private:
        NetworkBuilder();
        static Network create_connected_network(std::vector<int> layer_counts);
        static std::vector<Neuron> create_layer(int neuron_count);
        static void connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer);
        static void randomise_synapse_weights(std::vector<Neuron>& owning_layer);
        static void set_synapse_weights(std::vector<Neuron>& owning_layer, std::vector<SynapseData> synapse_data);

    public:
        static Network build_network(std::vector<int> layer_counts);
        static Network build_network(std::vector<int> layer_counts, NetworkData network_data);
};

#endif
