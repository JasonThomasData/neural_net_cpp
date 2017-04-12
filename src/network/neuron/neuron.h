#ifndef Neuron_h
#define Neuron_h

#include "../synapse/synapse.h"
#include <vector>

/* The neuron is responsible for owning the Soma, and has its own_output to send to other neurons
 * via Synapses (in biology, via an Axon and its Terminals). Its combined_incoming_values can be
 * retrieved for backpropagation.
 */

class Neuron
{
    public:
        Neuron();
        double incoming_values;
        double outgoing_value;
        double target_value;
        double error_value;
        std::vector<Synapse> incoming_synapses;
        std::vector<Synapse> outgoing_synapses;
        Synapse& add_incoming_synapse(Synapse incoming_synapse);
        void add_outgoing_synapse(Synapse& outgoing_synapse);
};

#endif
