#ifndef Network_h
#define Network_h

#include <vector>
#include "neuron/input.h"
#include "neuron/neuron.h"

/* The Network is the container for the model of Neurons and Synapses, and how those interact. 
 * Other than initialisation, this should be thought of as a passive thing that other classes
 * manipulate. */

class Network
{
    private:
        void connect_input_hidden_layer(std::vector<InputNeuron>& from_layer, std::vector<Neuron>& to_layer);
        void connect_hidden_output_layer(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer);
        void add_neurons_to_input_layer(std::vector<InputNeuron>&, int neuron_count);
        void add_neurons_to_layer(std::vector<Neuron>&, int neuron_count);

    public:
        float total_error;
        std::vector<InputNeuron> input_layer;
        std::vector<Neuron> hidden_layer;
        std::vector<Neuron> output_layer;
        Network(int input_count, int hidden_count, int output_count);
};

#endif
