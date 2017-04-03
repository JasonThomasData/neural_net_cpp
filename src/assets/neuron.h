#ifndef Neuron_h
#define Neuron_h

#include "soma.h"

/* The neuron is responsible for owning the Soma, and has its own output to send to other neurons
 * via Synapses (in biology, via an Axon and its Terminals).
 */

class Synapse;

class Neuron : private Soma
{
    private:
        float output_value;

    public:
        Neuron(float init_output_value, float init_threshold);
        void add_synapse(Synapse& new_synapse);
        void set_output_value();
        float get_output_value();
};

#endif
