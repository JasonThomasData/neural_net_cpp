#ifndef Neuron_h
#define Neuron_h

#include "../soma/soma.h"
#include "../synapse/synapse.h"
#include "interface.h"

/* The neuron is responsible for owning the Soma, and has its own_output to send to other neurons
 * via Synapses (in biology, via an Axon and its Terminals). Its combined_incoming_values can be
 * retrieved for backpropagation.
 */

class Neuron: public NeuronInterface
{
    private:
        float incoming_values;
        float outgoing_value;
        Soma soma;
    public:
        Neuron();
        std::vector<Synapse> incoming_synapses;
        std::vector<Synapse> outgoing_synapses;
        Synapse& add_incoming_synapse(Synapse incoming_synapse);
        void add_outgoing_synapse(Synapse& outgoing_synapse);
        void set_in_out_values();
        float target_value;
        float get_outgoing_value() override;
        float get_incoming_values() override;
};

#endif
