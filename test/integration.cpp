#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "../src/assets/neuron_interface.h"
#include "../src/assets/input_neuron.h"
#include "../src/assets/synapse.h"
#include "../src/assets/neuron.h"
#include "../src/assets/soma.h"
#include <iostream>


TEST_CASE( "synapse - get from_neuron's output_value #1 ") {

    /* InputNeuron has a public data member called output_value. This is the first layer. */
    InputNeuron from_neuron;
    from_neuron.outgoing_value = 0.5;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.0;

    float expected_result = 0.5;
    float actual_result = new_synapse.get_weighted_incoming_value();
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "synapse - get from_neuron's output_value #2 ") {

    InputNeuron from_neuron;
    from_neuron.outgoing_value = 4.0;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 0.75;

    float expected_result = 3.0;
    float actual_result = new_synapse.get_weighted_incoming_value();
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "synapse - get to_neuron's incoming_values ") {

    InputNeuron from_neuron1;
    from_neuron1.outgoing_value = 4.0;
    InputNeuron from_neuron2;
    from_neuron2.outgoing_value = 8.0;

    Neuron to_neuron;

    Synapse new_synapse1(from_neuron1, to_neuron);
    new_synapse1.weight = 0.75;
    Synapse new_synapse2(from_neuron2, to_neuron);
    new_synapse2.weight = 0.5;
    
    to_neuron.add_incoming_synapse(new_synapse1);
    to_neuron.add_incoming_synapse(new_synapse2);
    to_neuron.set_in_out_values();

    /* to_neuron will have the incoming values 4.0*0.75 + 8.0*0.5*/
    float expected_result = 7.0;
    float actual_result = new_synapse1.to_neuron.get_incoming_values();
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "synapse - update the weight with the value to change, would occur during back propagation") {

    Neuron from_neuron;
    Neuron to_neuron;
    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.0;

    float change_value = 0.4;
    new_synapse.update_weight(change_value);

    float expected_result = 0.6;
    float actual_result = new_synapse.weight;
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "soma - test this soma's sum function works - combine all incoming values")
{
    /* Both synapses have the same to neuron and it's not used in the function.
     */

    Neuron to_neuron;

    InputNeuron from_neuron_1;
    from_neuron_1.outgoing_value = 0.7;
    InputNeuron from_neuron_2;
    from_neuron_2.outgoing_value = 0.25;

    Synapse new_synapse_1(from_neuron_1, to_neuron);
    new_synapse_1.weight = 0.5;
    Synapse new_synapse_2(from_neuron_2, to_neuron);
    new_synapse_2.weight = 0.8;
    
    Soma soma;
    soma.incoming_synapses.emplace_back(new_synapse_1);
    soma.incoming_synapses.emplace_back(new_synapse_2);

    /* Result = 0.7*0.5 + 0.25*0.8 = 0.55 */
    float expected_result = 0.55;
    float actual_result = soma.calculate_incoming_values();
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "soma - test this soma's activation function works.")
{
    /* This is logistic regression, check the soma.cpp file */
    /* Also, watch tests that return floats, as returned floats have a max precision of 5 decimal
     * places.
     */

    Soma soma;

    float test_value_1 = 0.0;
    float actual_result_1 = soma.activate(test_value_1);
    float expected_result_1 = 0.5;
    REQUIRE(actual_result_1 == expected_result_1);

    float test_value_2 = 0.5;
    float actual_result_2 = soma.activate(test_value_2);
    float expected_result_2 = 0.622459;
    REQUIRE(actual_result_2 == expected_result_2);

    float test_value_3 = 1.0;
    float actual_result_3 = soma.activate(test_value_3);
    float expected_result_3 = 0.73106;
    REQUIRE(actual_result_3 == expected_result_3);

    /* I can't think of a situation where incoming values would be below zero, unless the weights on
     * synapses were negative, and I guess that could happen. It could occur if the activation was
     * using another function, like TanH.
     */
    float test_value_4 = -1.0;
    float actual_result_4 = soma.activate(test_value_4);
    float expected_result_4 = 0.26894;
    REQUIRE(actual_result_4 == expected_result_4);
}

TEST_CASE( "neuron - activate, via one incoming synapse #1 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    InputNeuron neuron1;
    neuron1.outgoing_value = 1.0;

    Neuron neuron2;

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.8;
    neuron2.add_incoming_synapse(new_synapse);

    /* Incoming weights are equal to 1.0*0.8 = 0.8 */
    neuron2.set_in_out_values();

    float expected_result = 0.689974;
    float actual_result = neuron2.get_outgoing_value();
    REQUIRE(actual_result == expected_result);
}

TEST_CASE( "neuron - activate, via one incoming synapse #2 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    InputNeuron neuron1;
    neuron1.outgoing_value = 0.8;

    Neuron neuron2;

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.5;
    neuron2.add_incoming_synapse(new_synapse);

    /* Incoming weights are equal to 0.5*0.8 = 0.4*/
    neuron2.set_in_out_values();

    float expected_result = 0.598688;
    float actual_result = neuron2.get_outgoing_value();
    REQUIRE(actual_result == expected_result);
}


TEST_CASE( "neuron - activate, via several incoming synapses ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    InputNeuron neuron1;
    neuron1.outgoing_value = 0.4;

    InputNeuron neuron2;
    neuron2.outgoing_value = 1.0;

    InputNeuron neuron3;
    neuron3.outgoing_value = 0.3;

    Neuron neuron4;

    Synapse new_synapse_1(neuron1, neuron4);
    new_synapse_1.weight = 0.75;
    Synapse new_synapse_2(neuron2, neuron4);
    new_synapse_2.weight = 0.2;
    Synapse new_synapse_3(neuron3, neuron4);
    new_synapse_3.weight = 0.5;

    neuron4.add_incoming_synapse(new_synapse_1);
    neuron4.add_incoming_synapse(new_synapse_2);
    neuron4.add_incoming_synapse(new_synapse_3);

    neuron4.set_in_out_values();

    /* Incoming values should be = 0.4*0.75 + 1.0*0.2 + 0.3*0.5 = 0.65 */
    float expected_result = 0.65701;
    float actual_result = neuron4.get_outgoing_value();
    REQUIRE(actual_result == expected_result);
}

