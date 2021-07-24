#include <iostream>

#include "../../lib/json.hpp"

#include "../network/network.h"
#include "parsed_data.h"
#include "json_parser.h"
#include "from_json.h"
#include "to_json.h"

TrainingData JsonParser::parse_training_data_from_json(nlohmann::json json_data)
{
    TrainingData training_data;
    FromJson::structure(training_data, json_data);
    FromJson::learning_rate(training_data, json_data);
    FromJson::target_total_error(training_data, json_data);
    FromJson::training_set(training_data, json_data);
    return training_data;
}

nlohmann::json JsonParser::parse_network_data_to_json(Network& network)
{
    // The hidden layer has incoming synapse weights, and so does the output layer. The input layer has no inoming synpapses.
    nlohmann::json json_data;
    ToJson::structure(network, json_data);
    ToJson::synapse_weights(network, json_data);
    return json_data;
}

NetworkData JsonParser::parse_network_data_from_json(nlohmann::json json_data)
{
    NetworkData network_data;
    FromJson::structure(network_data, json_data);
    FromJson::layers(network_data, json_data);
    return network_data;
}

NewData JsonParser::parse_new_data_from_json(nlohmann::json json_data)
{
    NewData new_data;
    FromJson::new_data(new_data, json_data);
    return new_data;
}
