#ifndef Neuron_h
#define Neuron_h

#include "soma.h"
#include "neuron_interface.h"

/* The neuron is responsible for owning the Soma, and has its own output to send to other neurons
 * via Synapses (in biology, via an Axon and its Terminals).
 */

class Synapse;

class Neuron: private Soma, public NeuronInterface
{
    private:
        float output_value;

    public:
        Neuron();
        void add_synapse(Synapse& new_synapse);
        void set_output_value();
        float get_output_value() override;
};

#endif
