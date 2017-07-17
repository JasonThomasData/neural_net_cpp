#include <memory>
#include "../synapse/i_synapse.h"
#include "neuron.h"

Neuron::Neuron(){}

/* When this new_synapse is added in place, return a reference added_synapse to add to the opposite
 * Neuron that is attached to this Synapse. This Neuron has ownership. This requires a unique
 * pointer, because a vector cannot construct an abstract class (ISynapse).
 * Added as a unique_ptr because the ISynapse can not be added, since it's an abstract class.
 */
std::shared_ptr<ISynapse>& Neuron::add_incoming_synapse(std::shared_ptr<ISynapse> new_incoming_synapse)
{
    incoming_synapses.emplace_back(std::move(new_incoming_synapse));
    std::shared_ptr<ISynapse>& added_synapse = incoming_synapses.back();
    return added_synapse;
}

void Neuron::add_outgoing_synapse(std::shared_ptr<ISynapse>& new_outgoing_synapse)
{
    outgoing_synapses.emplace_back(new_outgoing_synapse);
}

