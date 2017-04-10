#include "../catch.h"
#include "../../src/classifier/classifier.h"
#include "../../src/network/network.h"
#include <vector>

TEST_CASE( "classifier - set inputs") {

    int input_count = 2;
    int hidden_count = 3;
    int output_count = 1;

    Network neural_network(input_count, hidden_count, output_count);

    Classifier classifier(neural_network);

    std::vector<int> update_values;
    update_values.emplace_back(0);
    update_values.emplace_back(1);

    classifier.set_input_neurons(update_values);

    int actual_result1 = neural_network.input_layer.at(0).outgoing_value;
    int expected_result1 = 0;
    REQUIRE(actual_result1 == expected_result1);

    int actual_result2 = neural_network.input_layer.at(1).outgoing_value;
    int expected_result2 = 1;
    REQUIRE(actual_result2 == expected_result2);

}

TEST_CASE( "classifier - set inputs, fail cause the inputs are wrong size.") {

    int input_count = 2;
    int hidden_count = 3;
    int output_count = 1;

    Network neural_network(input_count, hidden_count, output_count);

    Classifier classifier(neural_network);

    std::vector<int> update_values;
    update_values.emplace_back(0);
    update_values.emplace_back(1.5);
    update_values.emplace_back(1);

    REQUIRE_THROWS( classifier.set_input_neurons(update_values) );

}

/* This is a large test, and requires the neurons to be using logistic regression for activation */
TEST_CASE( "classifier - feed forward") {

    int input_count = 2;
    int hidden_count = 2;
    int output_count = 1;

    Network neural_network(input_count, hidden_count, output_count);
    
    /* For this test, we need to know exactly what the Synapse weights are. */
    neural_network.hidden_layer.at(0).incoming_synapses.at(0).weight = 0.5;
    neural_network.hidden_layer.at(0).incoming_synapses.at(1).weight = 0.2;
    neural_network.hidden_layer.at(1).incoming_synapses.at(0).weight = 0.6;
    neural_network.hidden_layer.at(1).incoming_synapses.at(1).weight = 0.5;
    neural_network.output_layer.at(0).incoming_synapses.at(0).weight = 0.7;
    neural_network.output_layer.at(0).incoming_synapses.at(1).weight = 0.3;

    Classifier classifier(neural_network);

    /* This is to make sure the initial inputs have outgoing_values */
    std::vector<int> update_values;
    update_values.emplace_back(0);
    update_values.emplace_back(1);

    classifier.set_input_neurons(update_values);

    classifier.classify();

    float actual_result = neural_network.output_layer.at(0).outgoing_value;
    float expected_result = 0.63914;
    REQUIRE( Approx(actual_result) == expected_result);
}
