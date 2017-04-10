#include "../catch.h"
#include "../../src/network/network.h"

TEST_CASE( "network - initialise, add neurons to layers ") {

    int input_count = 4;
    int hidden_count = 7;
    int output_count = 3;

    Network neural_network(input_count, hidden_count, output_count);

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

void helper()
{
    int input_count = 4;
    int hidden_count = 0;
    int output_count = 3;
    Network neural_network(input_count, hidden_count, output_count);
}
TEST_CASE( "network - initialise, but throw an error if the layers are wrong ") {
    REQUIRE_THROWS( helper() );
}

/* Rather than assert the result, if this doesn't throw an error then it's fine.
 * This is not how the neurons are accessed, but, in a layer if the nth neuron's nth
 * incoming/outgoing synapse can call that function, then the neurons are connected. 
 */
TEST_CASE( "network - initialise, connect neurons between layers with synapses") {

    int input_count = 2;
    int hidden_count = 2;
    int output_count = 2;

    Network neural_network(input_count, hidden_count, output_count);

    /* Hidden layer */
    neural_network.hidden_layer.at(0).outgoing_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).incoming_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).outgoing_synapses.at(1).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(0).incoming_synapses.at(1).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).outgoing_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).incoming_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).outgoing_synapses.at(1).get_from_neuron_weighted_outgoing_value();
    neural_network.hidden_layer.at(1).incoming_synapses.at(1).get_from_neuron_weighted_outgoing_value();

    /* Output layer */
    neural_network.output_layer.at(0).incoming_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(0).incoming_synapses.at(1).get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(1).incoming_synapses.at(0).get_from_neuron_weighted_outgoing_value();
    neural_network.output_layer.at(1).incoming_synapses.at(1).get_from_neuron_weighted_outgoing_value();
}

