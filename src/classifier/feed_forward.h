#include <memory>
#include <vector>
#include "../synapse/i_synapse.h"
#include "../neuron/neuron.h"

namespace FeedForward
{
    double calculate_incoming_values(std::vector<std::unique_ptr<ISynapse>>& incoming_synapses);
    double activate(double incoming_values);
    void update_neuron(Neuron& neuron);
    void update_layer(std::vector<Neuron>& layer);
};
