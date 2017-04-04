#ifndef NeuronInterface_h
#define NeuronInterface_h

/* This is the class that is inherited into the Neurons (Input and Neuron) so that we can pass by
 * reference to interface when we need them.
 */

class NeuronInterface
{
    public:
        virtual float get_outgoing_value() =0;
        virtual float get_incoming_values() =0;
};

#endif
