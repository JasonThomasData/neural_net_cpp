#include <stdexcept>
#include <vector>
#include <memory>
#include <functional>

#include "network.h"
#include "synapse/synapse.h"
#include "synapse/i_synapse.h"

Network::Network(std::vector<Neuron> input_layer, std::vector<Neuron> hidden_layer, std::vector<Neuron> output_layer)
    :input_layer(std::move(input_layer)),
     hidden_layer(std::move(hidden_layer)),
     output_layer(std::move(output_layer))
{
    epoch_average_total_error = 0.0;
}

