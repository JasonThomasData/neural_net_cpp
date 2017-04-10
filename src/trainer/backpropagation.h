#ifndef Backpropagation_h
#define Backpropagation_h

#include <vector>
#include "../network/synapse/synapse.h"
#include "../network/neuron/neuron.h"

/* This class has all logic to train the network. Set as a private data member inside Trainer().
 * This class will do all the work relating to backpropagation. 
 */

class Backpropagation
{
public:
    Backpropagation();
    void output_layer_set_synapse_weight(Synapse& synapse, float neuron_error);
    void output_layer_set_neuron_error(Neuron& neuron);
    void output_layer_neuron(Neuron& neuron);
    void output_layer(std::vector<Neuron>& output_layer);
    void hidden_layer_set_synapse_weight(Synapse& synapse, float total_neuron_error);
    float hidden_layer_get_total_neuron_errors(std::vector<Synapse>& outgoing_synapse);
    void hidden_layer_neuron(Neuron& neuron);
    void hidden_layer(std::vector<Neuron>& hidden_layer);
};

#endif
