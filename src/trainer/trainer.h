#ifndef Trainer_h
#define Trainer_h

#include <vector>

#include "backpropagation.h"

/* The Trainer is the agent to do backpropagation and calculate errors for the Network. An Epoch is
 * one full round of training the network with all documents. */


class Neuron;      //  ../neuron/neuron.h 
class Network;     //  ../network/network.h

class Trainer
{
    private:
        Network& network;
        Backpropagation backpropagation;
        double calculate_error(Neuron& neuron);
        double learning_rate;
    public:
        Trainer(Network& network, double learning_rate);
        double calculate_total_error(std::vector<Neuron>& output_layer);
        int epoch;
        void train();
        void set_target_values(std::vector<double> new_target_values);
};

#endif
