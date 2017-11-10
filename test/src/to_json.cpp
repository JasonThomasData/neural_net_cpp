#include <vector>

#include "../../lib/catch.h"
#include "../../lib/json.hpp"
#include "../../src/json_parser/to_json.h"
#include "../../src/network/network.h"
#include "../../src/network_builder/network_builder.h"

TEST_CASE( "ToJson - integration test - structure to json")
{
    std::vector<int> network_structure = {2,3,1};
    Network network = NetworkBuilder::create_network(network_structure);

    nlohmann::json json_data;

    ToJson::structure(network, json_data);

    std::vector<int> actual_targets = json_data["structure"];
    std::vector<int> expected_targets = {2, 3, 1};
    REQUIRE(actual_targets == expected_targets);
}

TEST_CASE( "ToJson - integration test - layers of synapse weights to json")
{
    /* This network when dumped as JSON would look like:
     *
     * {
     *     "layers": {
     *         "hidden" : [
     *             {
     *                 "neuron_index": 0,
     *                 "synapse_index": 0,
     *                 "synapse_weight": 0.1,
     *             },
     *             {
     *                 "neuron_index": 0,
     *                 "synapse_index": 1,
     *                 "synapse_weight": N/A,
     *             },
     *             {
     *                 "neuron_index": 1,
     *                 "synapse_index": 0,
     *                 "synapse_weight": N/A,
     *             },
     *             {
     *                 "neuron_index": 1,
     *                 "synapse_index": 1,
     *                 "synapse_weight": -1.0,
     *             },
     *             {
     *                 "neuron_index": 2,
     *                 "synapse_index": 0,
     *                 "synapse_weight": 0.510,
     *             },
     *             {
     *                 "neuron_index": 2,
     *                 "synapse_index": 1,
     *                 "synapse_weight": N/A,
     *             }
     *         ],
     *         "output" : [
     *             {
     *                 "neuron_index": 0,
     *                 "synapse_index": 0,
     *                 "synapse_weight": 0.001,
     *             },
     *             {
     *                 "neuron_index": 0,
     *                 "synapse_index": 2,
     *                 "synapse_weight": 2.0,
     *             }
     *         ]
     *     },
     *     structure: [2,3,1]
     * }
     *
     *
     */
    std::vector<int> network_structure = {2,3,1};
    Network network = NetworkBuilder::create_network(network_structure);
    network.hidden_layer.at(0).incoming_synapses.at(0)->set_weight(0.1);
    network.hidden_layer.at(1).incoming_synapses.at(1)->set_weight(-1.0);
    network.hidden_layer.at(2).incoming_synapses.at(0)->set_weight(0.51);
    network.output_layer.at(0).incoming_synapses.at(0)->set_weight(0.001);
    network.output_layer.at(0).incoming_synapses.at(2)->set_weight(2.0);

    nlohmann::json json_data;

    ToJson::synapse_weights(network, json_data);

    nlohmann::json json_data_hidden_0 = json_data["layers"]["hidden"].at(0);
    nlohmann::json json_data_hidden_3 = json_data["layers"]["hidden"].at(3);
    nlohmann::json json_data_hidden_4 = json_data["layers"]["hidden"].at(4);
    nlohmann::json json_data_output_0 = json_data["layers"]["output"].at(0);
    nlohmann::json json_data_output_2 = json_data["layers"]["output"].at(2);

    REQUIRE(0 == json_data_hidden_0["neuron_index"]);
    REQUIRE(0 == json_data_hidden_0["synapse_index"]);
    REQUIRE(0.1 == json_data_hidden_0["synapse_weight"]);

    REQUIRE(1 == json_data_hidden_3["neuron_index"]);
    REQUIRE(1 == json_data_hidden_3["synapse_index"]);
    REQUIRE(-1.0 == json_data_hidden_3["synapse_weight"]);

    REQUIRE(2 == json_data_hidden_4["neuron_index"]);
    REQUIRE(0 == json_data_hidden_4["synapse_index"]);
    REQUIRE(0.51 == json_data_hidden_4["synapse_weight"]);

    REQUIRE(0 == json_data_output_0["neuron_index"]);
    REQUIRE(0 == json_data_output_0["synapse_index"]);
    REQUIRE(0.001 == json_data_output_0["synapse_weight"]);

    REQUIRE(0 == json_data_output_2["neuron_index"]);
    REQUIRE(2 == json_data_output_2["synapse_index"]);
    REQUIRE(2.0 == json_data_output_2["synapse_weight"]);
}
