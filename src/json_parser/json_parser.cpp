#include "../../lib/json.hpp"

#include "../network/network.h"
#include "parsed_data.h"
#include "json_parser.h"

JsonParser::JsonParser(){}

TrainingData JsonParser::parse_training_data_from_json(nlohmann::json json_data)
{
    TrainingData training_data;
    from_json.structure(training_data, json_data);
    from_json.learning_rate(training_data, json_data);
    from_json.target_total_error(training_data, json_data);
    from_json.training_set(training_data, json_data);
    return training_data;
}

nlohmann::json JsonParser::parse_network_data_to_json(Network& network)
{
    nlohmann::json json_data;
    to_json.structure(network, json_data);
    to_json.synapse_weights(network, json_data);
    return json_data;
}

