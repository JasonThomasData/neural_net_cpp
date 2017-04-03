#ifndef InputNeuron_h
#define InputNeuron_h

#include "neuron_interface.h"

/* The neuron is responsible for owning the Soma, and has its own output to send to other neurons
 * via Synapses (in biology, via an Axon and its Terminals).
 */

class InputNeuron : public NeuronInterface
{
    public:
        float output_value;
        InputNeuron();
        float get_output_value() override;
};

#endif
