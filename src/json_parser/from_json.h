#include "../../lib/json.hpp"

#include "parsed_data.h"

namespace FromJson
{
    void structure(DataCollection& data_collection, nlohmann::json json_data);
    void learning_rate(TrainingData& training_data, nlohmann::json json_data);
    void target_total_error(TrainingData& training_data, nlohmann::json json_data);
    void training_set(TrainingData& training_data, nlohmann::json json_data);
    void layers(NetworkData& network_data, nlohmann::json json_data);
    void one_layer(std::vector<SynapseData>& layer, nlohmann::json layer_json_data);
    void synapse(SynapseData& synapse_data, nlohmann::json synapse_json_data);
    void neuron_index(SynapseData& synapse_data, nlohmann::json json_data);
    void incoming_synapse_index(SynapseData& synapse_data, nlohmann::json json_data);
    void incoming_synapse_weight(SynapseData& synapse_data, nlohmann::json json_data);
};

