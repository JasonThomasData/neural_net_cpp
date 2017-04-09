#ifndef Trainer_h
#define Trainer_h

#include <vector>
#include "../network/network.h"
#include "../network/neuron/neuron.h"
#include "backpropagation.h"

/* The Trainer is the agent to do backpropagation and calculate errors for the Network. An Epoch is
 * one full round of training the network with all documents. */

class Trainer
{
    private:
        void calculate_error(Neuron& neuron);
        Network& network;
        Backpropagation backpropagation;
        float learning_rate;
    public:
        Trainer(Network& network, float learning_rate);
        void calculate_total_error(std::vector<Neuron> output_layer);
        int epoch;
        void train();
};

#endif
