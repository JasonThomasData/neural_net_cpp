#ifndef NetworkBuilder_h
#define NetworkBuilder_h

#include <vector>
#include "../network/network.h"

class NetworkBuilder
{
    private:
        NetworkBuilder();
        static void connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer);
        static std::vector<Neuron> create_layer(int neuron_count);
        static void randomise_synapse_weights(std::vector<Neuron>& owning_layer);

    public:
        static Network build_network(std::vector<int> layer_counts);
        static void set_synapse_weights(std::vector<int> weights);
        static void set_synapse_random_weights();
};

#endif
