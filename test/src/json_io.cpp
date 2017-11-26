#include "../../lib/catch.h"
#include "../../src/json_io/json_io.h"
#include "../../src/json_parser/parsed_data.h"

TEST_CASE( "JsonReader - unit test - test there's no file")
{
    std::string file_name = "totally not a real file";

    REQUIRE_THROWS( JsonIO::read_training_data(file_name) );
}

/*
 * This test uses test/training_data file, which is a Nand gate
 *
 *   structure 2,3,1
 *   learning_rate 0.15
 *   target_total_error 0.0005
 *   0,0 1
 *   0,1 1
 *   1,0 1
 *   1,1 0
 */

TEST_CASE( "reader - integration test - test training_data.json file is loaded and parsed")
{
    std::string file_name = "test/training_data.json";

    TrainingData test_training_data = JsonIO::read_training_data(file_name);

    std::vector<int> actual_structure = test_training_data.structure;
    std::vector<int> expected_structure = {2,3,1};
    REQUIRE(actual_structure == expected_structure);

    double actual_learning_rate = test_training_data.learning_rate;
    double expected_learning_rate = 0.15;
    REQUIRE(actual_learning_rate == expected_learning_rate);

    double actual_target_total_error = test_training_data.target_total_error;
    double expected_target_total_error = 0.0005;
    REQUIRE(actual_target_total_error == expected_target_total_error);

    std::vector<double> actual_data = test_training_data.training_set.at(2).input_values;
    std::vector<double> expected_data = {1.0, 0.0};
    REQUIRE(actual_data == expected_data);

    std::vector<double> actual_targets = test_training_data.training_set.at(3).target_values;
    std::vector<double> expected_targets = {0.0};
    REQUIRE(actual_targets == expected_targets);
}

TEST_CASE( "reader - integration test - test network_data.json is loaded and parsed")
{
    std::string file_name = "test/network_data.json";

    NetworkData test_network_data = JsonIO::read_network_data(file_name);

    std::vector<int> actual_structure = test_network_data.structure;
    std::vector<int> expected_structure = {2,3,1};
    REQUIRE(actual_structure == expected_structure);

    REQUIRE(test_network_data.hidden_layer.at(0).neuron_index == 0);
    REQUIRE(test_network_data.hidden_layer.at(0).incoming_synapse_index == 0);
    REQUIRE(test_network_data.hidden_layer.at(0).incoming_synapse_weight == 0.48445437552706);

    REQUIRE(test_network_data.hidden_layer.at(1).neuron_index == 0);
    REQUIRE(test_network_data.hidden_layer.at(1).incoming_synapse_index == 1);
    REQUIRE(test_network_data.hidden_layer.at(1).incoming_synapse_weight == -0.262612185918664);

    REQUIRE(test_network_data.hidden_layer.at(5).neuron_index == 2);
    REQUIRE(test_network_data.hidden_layer.at(5).incoming_synapse_index == 1);
    REQUIRE(test_network_data.hidden_layer.at(5).incoming_synapse_weight == -0.0199056665781298);

    REQUIRE(test_network_data.output_layer.at(0).neuron_index == 0);
    REQUIRE(test_network_data.output_layer.at(0).incoming_synapse_index == 0);
    REQUIRE(test_network_data.output_layer.at(0).incoming_synapse_weight == 1.02111633998853);

    REQUIRE(test_network_data.output_layer.at(2).neuron_index == 0);
    REQUIRE(test_network_data.output_layer.at(2).incoming_synapse_index == 2);
    REQUIRE(test_network_data.output_layer.at(2).incoming_synapse_weight == 0.53155378443106);
}
