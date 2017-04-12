#ifndef Network_h
#define Network_h

#include <vector>
#include "neuron/neuron.h"

/* The Network is the container for the model of Neurons and Synapses, and how those interact. 
 * Other than initialisation, this should be thought of as a passive thing that other classes
 * manipulate. */

class Network
{
    private:
        void connect_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer);
        void add_neurons_to_layer(std::vector<Neuron>&, int neuron_count);

    public:
        float epoch_average_total_error;
        std::vector<Neuron> input_layer;
        std::vector<Neuron> hidden_layer;
        std::vector<Neuron> output_layer;
        Network(int input_count, int hidden_count, int output_count);
};

#endif
