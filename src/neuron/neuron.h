#ifndef Neuron_h
#define Neuron_h

#include <vector>
#include <memory>

#include "../synapse/i_synapse.h"

class Neuron
{
    public:
        Neuron();
        double incoming_values;
        double outgoing_value;
        double target_value;
        double error_value;
        std::vector<std::unique_ptr<ISynapse>> incoming_synapses;
        std::vector<std::reference_wrapper<ISynapse>> outgoing_synapses;
        std::reference_wrapper<ISynapse> add_incoming_synapse(std::unique_ptr<ISynapse> new_incoming_synapse);
        void add_outgoing_synapse(std::reference_wrapper<ISynapse> new_outgoing_synapse);
};

#endif
