#ifndef NeuronInterface_h
#define NeuronInterface_h

/* This is the class that is inherited into the Neurons (Input and Neuron) so that we can pass by
 * reference to interface when we need them.
 */

class NeuronInterface
{
    public:
        virtual float get_output_value() =0;
};

#endif
