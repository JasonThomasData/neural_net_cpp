#ifndef Synapse_h
#define Synapse_h

/* A synapse is the connection between a biological neuron's axon terminal (outgoing value) and
 * another neuron's dendrite (incoming value). For this abstract concept, we'll just connect synapses
 * to to the Soma that each Neuron owns. In biological terms, this abstract synapse is effectively an
 * axon terminal and dendrite pair. This synapse is responsible for connecting two layers, and applying
 * weights to the incoming values.
 * A synapse will have a weight attached to it, to filter the incoming value, and the weight should
 * be available to the network to modify.
 */

#include "i_synapse.h"

class Neuron;

class Synapse: public ISynapse
{
    private:
        Neuron& from_neuron;
        Neuron& to_neuron;
        double weight;
    public:
        Synapse(Neuron& from_neuron, Neuron& to_neuron, double weight);
        double get_from_neuron_weighted_outgoing_value() override;
        double get_weight() override;
        void set_weight(double new_weight) override;
        Neuron& get_from_neuron() override;
        Neuron& get_to_neuron() override;
};

#endif
