#include "../../lib/catch.h"
#include "../../src/network/network.h"
#include "../../src/network_builder/network_builder.h"

TEST_CASE( "network_builder - integration test - initialise, add neurons to layers ")
{

    std::vector<int> layer_counts {4, 7, 3};

    Network neural_network = NetworkBuilder::build_network(layer_counts);

    int actual_result1 = neural_network.input_layer.size();
    int expected_result1 = 4;
    REQUIRE(actual_result1 == expected_result1);

    int actual_result2 = neural_network.hidden_layer.size();
    int expected_result2 = 7;
    REQUIRE(actual_result2 == expected_result2);

    int actual_result3 = neural_network.output_layer.size();
    int expected_result3 = 3;
    REQUIRE(Approx(actual_result3) == expected_result3);
}

void helper_int_too_low()
{
    std::vector<int> layer_counts {4, 0, 3};

    Network neural_network = NetworkBuilder::build_network(layer_counts);
}
void helper_wrong_type()
{
    std::vector<int> layer_counts {'a', 0, 3};

    Network neural_network = NetworkBuilder::build_network(layer_counts);
}
TEST_CASE( "network_builder - unit test - initialise, but throw an error if the layers are wrong ")
{
    REQUIRE_THROWS( helper_int_too_low() );
    REQUIRE_THROWS( helper_wrong_type() );
}

//Recycle this to test the network gets build properly
TEST_CASE( "network_builder - unit test - initialise, connect neurons between layers with synapses")
{
    std::vector<int> layer_counts {4, 7, 3};

    Network neural_network = NetworkBuilder::build_network(layer_counts);

    /* Hidden layer */
    neural_network.hidden_layer.at(0).outgoing_synapses.at(0).get().get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).incoming_synapses.at(0)->get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).outgoing_synapses.at(1).get().get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).incoming_synapses.at(1)->get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).outgoing_synapses.at(0).get().get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).incoming_synapses.at(0)->get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).outgoing_synapses.at(1).get().get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).incoming_synapses.at(1)->get_from_neuron_weighted_outgoing_value();

    /* Output layer */
    neural_network.output_layer.at(0).incoming_synapses.at(0)->get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(0).incoming_synapses.at(1)->get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(1).incoming_synapses.at(0)->get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(1).incoming_synapses.at(1)->get_from_neuron_weighted_outgoing_value();
}

