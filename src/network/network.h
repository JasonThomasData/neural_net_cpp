#ifndef Network_h
#define Network_h

#include <vector>
#include "neuron/neuron.h"

/* The Network is the container for the model of Neurons and Synapses, and how those interact. 
 * Other than initialisation, this should be thought of as a passive thing that other classes
 * manipulate. */

class Neuron; // neuron/neuron.h

class Network
{
    public:
        Network(std::vector<Neuron> input_layer,
                std::vector<Neuron> hidden_layer,
                std::vector<Neuron> output_layer);
        float epoch_average_total_error;
        std::vector<Neuron> input_layer;
        std::vector<Neuron> hidden_layer;
        std::vector<Neuron> output_layer;
};

#endif
