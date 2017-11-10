#include "../../lib/json.hpp"

#include "../network/network.h"

namespace ToJson
{
    void structure(Network& network, nlohmann::json& json_data);
    void synapse_weights(Network& network, nlohmann::json& json_data);
    nlohmann::json collect_synapse_data_in_layer(std::vector<Neuron>& layer);
    nlohmann::json create_synapse_json_object(int neuron_index, int synapse_index, double synapse_weight);
};
