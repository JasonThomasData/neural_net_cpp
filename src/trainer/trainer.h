#ifndef Trainer_h
#define Trainer_h

#include <vector>
#include "backpropagation.h"

/* The Trainer is the agent to do backpropagation and calculate errors for the Network. An Epoch is
 * one full round of training the network with all documents. */

class Network;
class Neuron;

class Trainer
{
    private:
        Network& network;
        Backpropagation backpropagation;
        float calculate_error(Neuron& neuron);
        float learning_rate;
    public:
        Trainer(Network& network, float learning_rate);
        float calculate_total_error(std::vector<Neuron>& output_layer);
        int epoch;
        void train();
        void set_target_values(std::vector<float>& new_target_values);
};

#endif
