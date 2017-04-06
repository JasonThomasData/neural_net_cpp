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

class NeuronInterface;

class Synapse
{
    private:
        NeuronInterface& from_neuron;
    public:
        NeuronInterface& to_neuron;
        Synapse(NeuronInterface& from_neuron, NeuronInterface& to_neuron);
        float weight = 0.5;
        float get_to_neuron_incoming_values();
        float get_from_neuron_weighted_outgoing_value();
        float get_from_neuron_outgoing_value();
};

#endif
