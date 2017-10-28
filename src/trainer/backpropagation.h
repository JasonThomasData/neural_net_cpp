#ifndef Backpropagation_h
#define Backpropagation_h

#include <memory>
#include <vector>
#include <functional>

/* This class has all logic to train the network. Set as a private data member inside Trainer().
 * This class will do all the work relating to backpropagation. 
 */

class Neuron;      //  ../neuron/neuron.h 
class ISynapse;    //  ../synapse/i_synapse.h

class Backpropagation
{
public:
    Backpropagation(double learning_rate);
    double learning_rate;
    void output_layer_set_synapse_weight(std::unique_ptr<ISynapse>& synapse, double neuron_error);
    void output_layer_set_neuron_error(Neuron& neuron);
    void output_layer_neuron(Neuron& neuron);
    void output_layer(std::vector<Neuron>& output_layer);
    void hidden_layer_set_synapse_weight(std::unique_ptr<ISynapse>& synapse, double logistic_derivative, double total_neuron_error);
    double hidden_layer_get_total_neuron_errors(std::vector<std::reference_wrapper<ISynapse>>& outgoing_synapse);
    void hidden_layer_neuron(Neuron& neuron);
    void hidden_layer(std::vector<Neuron>& hidden_layer);
};

#endif
