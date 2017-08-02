#ifndef FeedForward_h
#define FeedForward_h

#include <memory>
#include <vector>

/* This will be defined as a data member in the Classifier */

// With interface, these need to become ISynapse and INeuron

class ISynapse; //  ../network/synapse/i_synapse.h
class Neuron;  //  ../network/neuron/neuron.h

class FeedForward
{
    public:
        FeedForward();
        double calculate_incoming_values(std::vector<std::unique_ptr<ISynapse>>& incoming_synapses);
        double activate(double incoming_values);
        void update_neuron(Neuron& neuron);
        void update_layer(std::vector<Neuron>& layer);
};

#endif
