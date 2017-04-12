#include "../synapse/synapse.h"
#include "neuron.h"

Neuron::Neuron(){}

/* When this new_synapse is added in place, return a reference added_synapse to add to the opposite
 * Neuron that is attached to this Synapse. This Neuron has ownership.
 */
Synapse& Neuron::add_incoming_synapse(Synapse incoming_synapse)
{
    incoming_synapses.emplace_back(incoming_synapse);
    Synapse& added_synapse = incoming_synapses.back();
    return added_synapse;
}

/* The added_synapse is a reference to the new_synapse that was added to other Neuron, which is
 * connected to this Synapse.
 */
void Neuron::add_outgoing_synapse(Synapse& outgoing_synapse)
{
    outgoing_synapses.emplace_back(outgoing_synapse);
}

