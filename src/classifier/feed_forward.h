#ifndef FeedForward_h
#define FeedForward_h

#include <vector>

/* This will be defined as a data member in the Classifier */

class Synapse;
class Neuron;

class FeedForward
{
    public:
        FeedForward();
        double calculate_incoming_values(std::vector<Synapse>& incoming_synapses);
        double activate(double incoming_values);
        void update_neuron(Neuron& neuron);
        void update_layer(std::vector<Neuron>& layer);
};

#endif
