#include <vector>
#include <iostream>

#include "../../lib/catch.h"
#include "../../lib/json.hpp"
#include "../../src/json_parser/from_json.h"
#include "../../src/json_parser/parsed_data.h"

TEST_CASE( "FromJson - unit test - structure from json")
{
    nlohmann::json json_data;
    json_data["structure"] = {2,3,1};
    TrainingData training_data;

    FromJson::structure(training_data, json_data);

    std::vector<int> actual = training_data.structure;
    std::vector<int> expected = {2, 3, 1};
    REQUIRE(actual == expected);
}

TEST_CASE( "FromJson - unit test - target_total_error from json")
{
    nlohmann::json json_data;
    json_data["target_total_error"] = 0.03;
    TrainingData training_data;

    FromJson::target_total_error(training_data, json_data);

    double actual = training_data.target_total_error;
    double expected = 0.03;
    REQUIRE(actual == expected);
}

TEST_CASE( "FromJson - unit test - learning_rate from json")
{
    nlohmann::json json_data;
    json_data["learning_rate"] = 0.1;
    TrainingData training_data;

    FromJson::learning_rate(training_data, json_data);

    double actual = training_data.learning_rate;
    double expected = 0.1;
    REQUIRE(actual == expected);
}

TEST_CASE( "FromJson - unit test - training_set from json")
{
    nlohmann::json json_data; 
    json_data["training_set"] = {};
    nlohmann::json training_document_0 = nlohmann::json::object({ {"input_values", {0.4780302414,1.0}},
                                                                  {"target_values", {0.0}} });
    nlohmann::json training_document_1 = nlohmann::json::object({ {"input_values", {0.0,0.0}},
                                                                  {"target_values", {1.0}} });
    json_data["training_set"].emplace_back(training_document_0);
    json_data["training_set"].emplace_back(training_document_1);

    TrainingData training_data;

    FromJson::training_set(training_data, json_data);

    std::vector<double> actual_input_values_0 = training_data.training_set.at(0).input_values;
    std::vector<double> expected_input_values_0 = {0.4780302414, 1.0};
    REQUIRE(actual_input_values_0 == expected_input_values_0);

    std::vector<double> actual_target_values_1 = training_data.training_set.at(1).target_values;
    std::vector<double> expected_target_values_1 = {1.0};
    REQUIRE(actual_target_values_1 == expected_target_values_1);
}

TEST_CASE( "FromJson - unit test - synapse data")
{
    nlohmann::json synapse_data_json = nlohmann::json::object({ {"neuron_index", 1},
                                                                {"incoming_synapse_index", 0},
                                                                {"incoming_synapse_weight", 1.64853242053333} });

    SynapseData synapse_data;

    FromJson::synapse(synapse_data, synapse_data_json);

    REQUIRE(synapse_data.neuron_index == 1);
    REQUIRE(synapse_data.incoming_synapse_index == 0);
    REQUIRE(synapse_data.incoming_synapse_weight == 1.64853242053333);
}

TEST_CASE( "FromJson - unit test - one_layer")
{

    nlohmann::json synapse_data_0 = nlohmann::json::object({ {"neuron_index", 0},
                                                             {"incoming_synapse_index", 0},
                                                             {"incoming_synapse_weight", 1.64853242053333} });

    nlohmann::json synapse_data_1 = nlohmann::json::object({ {"neuron_index", 0},
                                                             {"incoming_synapse_index", 1},
                                                             {"incoming_synapse_weight", 2.02344342053543} });

    nlohmann::json synapse_data_2 = nlohmann::json::object({ {"neuron_index", 1},
                                                             {"incoming_synapse_index", 0},
                                                             {"incoming_synapse_weight", -10.2344342053543} });

    nlohmann::json synapse_data_3 = nlohmann::json::object({ {"neuron_index", 1},
                                                             {"incoming_synapse_index", 1},
                                                             {"incoming_synapse_weight", 21.02344322230} });

    nlohmann::json layer_json_data = {};
    layer_json_data.emplace_back(synapse_data_0);
    layer_json_data.emplace_back(synapse_data_1);
    layer_json_data.emplace_back(synapse_data_2);
    layer_json_data.emplace_back(synapse_data_3);

    NetworkData network_data;

    FromJson::one_layer(network_data.hidden_layer, layer_json_data);

    REQUIRE(network_data.hidden_layer.at(0).neuron_index == 0);
    REQUIRE(network_data.hidden_layer.at(0).incoming_synapse_index == 0);
    REQUIRE(network_data.hidden_layer.at(0).incoming_synapse_weight == 1.64853242053333);

    REQUIRE(network_data.hidden_layer.at(1).neuron_index == 0);
    REQUIRE(network_data.hidden_layer.at(1).incoming_synapse_index == 1);
    REQUIRE(network_data.hidden_layer.at(1).incoming_synapse_weight == 2.02344342053543);

    REQUIRE(network_data.hidden_layer.at(2).neuron_index == 1);
    REQUIRE(network_data.hidden_layer.at(2).incoming_synapse_index == 0);
    REQUIRE(network_data.hidden_layer.at(2).incoming_synapse_weight == -10.2344342053543);

    REQUIRE(network_data.hidden_layer.at(3).neuron_index == 1);
    REQUIRE(network_data.hidden_layer.at(3).incoming_synapse_index == 1);
    REQUIRE(network_data.hidden_layer.at(3).incoming_synapse_weight == 21.02344322230);
}
