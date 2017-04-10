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
        float calculate_incoming_values(std::vector<Synapse>& incoming_synapses);
        float activate(float incoming_values);
        void update_neuron(Neuron& neuron);
        void update_layer(std::vector<Neuron>& layer);
};

#endif
