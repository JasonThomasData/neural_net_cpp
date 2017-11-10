#include "../../lib/json.hpp"

#include "../network/network.h"
#include "to_json.h"

void ToJson::structure(Network& network, nlohmann::json& json_data)
{
    int input_neuron_count = network.input_layer.size();
    int hidden_neuron_count = network.hidden_layer.size();
    int output_neuron_count = network.output_layer.size();

    json_data["structure"] = {input_neuron_count, hidden_neuron_count, output_neuron_count};
}

void ToJson::synapse_weights(Network& network, nlohmann::json& json_data)
{
    std::vector<Neuron>& hidden_layer = network.hidden_layer;
    nlohmann::json hidden_layer_json_data = collect_synapse_data_in_layer(hidden_layer);

    std::vector<Neuron>& output_layer = network.output_layer;
    nlohmann::json output_layer_json_data = collect_synapse_data_in_layer(output_layer);

    json_data["layers"] = nlohmann::json::object({ {"hidden", hidden_layer_json_data },
                                                   {"output", output_layer_json_data } });
}

nlohmann::json ToJson::collect_synapse_data_in_layer(std::vector<Neuron>& layer)
{
    nlohmann::json layer_json_data = {};
    int neuron_count = layer.size();
    for(int neuron_index=0; neuron_index<neuron_count; neuron_index++)
    {
        int incoming_synapse_count = layer.at(neuron_index).incoming_synapses.size();
        for(int synapse_index=0; synapse_index<incoming_synapse_count; synapse_index++)
        {
            double synapse_weight = layer.at(neuron_index).incoming_synapses.at(synapse_index)->get_weight();
            nlohmann::json synapse_data = create_synapse_json_object(neuron_index, synapse_index, synapse_weight);
            layer_json_data.emplace_back(synapse_data);
        }
    }
    return layer_json_data;
}

nlohmann::json ToJson::create_synapse_json_object(int neuron_index, int synapse_index, double synapse_weight)
{
    nlohmann::json synapse_data = nlohmann::json::object({ {"neuron_index", neuron_index },
                                                           {"synapse_index", synapse_index },
                                                           {"synapse_weight", synapse_weight } });
    return synapse_data;
}
