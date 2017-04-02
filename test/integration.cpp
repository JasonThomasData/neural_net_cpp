#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.h"
#include "../src/assets/synapse.h"
#include "../src/assets/neuron.h"
#include "../src/assets/soma.h"


TEST_CASE( "synapse - get from_neuron's value #1 ") {

    float init_output_value = 0.5;
    float null_not_needed = 0.0;
    Neuron from_neuron(init_output_value, null_not_needed);
    Neuron to_neuron(null_not_needed, null_not_needed);

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.0;

    float expected_result = 0.5;
    REQUIRE(new_synapse.get_weighted_incoming_value() == expected_result);
}

TEST_CASE( "synapse - get from_neuron's value #2 ") {

    float init_output_value = 4.0;
    float null_not_needed = 0.0;
    Neuron from_neuron(init_output_value, null_not_needed);
    Neuron to_neuron(null_not_needed, null_not_needed);

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 0.75;

    float expected_result = 3.0;
    REQUIRE(new_synapse.get_weighted_incoming_value() == expected_result);
}

TEST_CASE( "synapse - update the weight with the value to change, would occur during back propagation") {

    float null_not_needed = 0.0;
    Neuron from_neuron(null_not_needed, null_not_needed);
    Neuron to_neuron(null_not_needed, null_not_needed);
    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.0;

    float change_value = 0.4;
    new_synapse.update_weight(change_value);

    float expected_result = 0.6;

    REQUIRE(new_synapse.weight == expected_result);
}

TEST_CASE( "soma - test this soma's sum function works - combine all incoming values")
{
    /* Both synapses have the same to neuron and it's not used in the function.
     */

    float null_not_needed = 0.0;
    Neuron to_neuron(null_not_needed, null_not_needed);

    float init_output_value_1 = 0.7;
    Neuron from_neuron_1(init_output_value_1, null_not_needed);
    float init_output_value_2 = 0.25;
    Neuron from_neuron_2(init_output_value_2, null_not_needed);

    Synapse new_synapse_1(from_neuron_1, to_neuron);
    new_synapse_1.weight = 0.5;
    Synapse new_synapse_2(from_neuron_2, to_neuron);
    new_synapse_2.weight = 0.8;
    
    Soma soma(null_not_needed);
    soma.all_synapses.emplace_back(new_synapse_1);
    soma.all_synapses.emplace_back(new_synapse_2);

    /* Result = 0.7*0.5 + 0.25*0.8 = 0.55 */
    float expected_result = 0.55;
    REQUIRE(soma.add_incoming_values() == expected_result);
}

TEST_CASE( "soma - test this soma's activation function works.")
{
    /* The function is a step function. If the given value is larger than the threshold, it returns
     * 1, otherwise 0
     * Important to note, the threshold will be compared to the sum of all incoming values, with
     * weights applied by the individual synapses.
     */
   
    float init_threshold = 0.5;
    Soma soma(init_threshold);

    float test_value_1 = 0.7;
    float expected_result_1 = 1.0;
    REQUIRE(soma.activate(test_value_1) == expected_result_1);

    float test_value_2 = 0.5;
    float expected_result_2 = 1.0;
    REQUIRE(soma.activate(test_value_2) == expected_result_2);

    float test_value_3 = 0.499;
    float expected_result_3 = 0.0;
    REQUIRE(soma.activate(test_value_3) == expected_result_3);

    float test_value_4 = 0.0001;
    float expected_result_4 = 0.0;
    REQUIRE(soma.activate(test_value_4) == expected_result_4);
}

TEST_CASE( "neuron - activate, via one synapse #1 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    float null_not_needed = 0.0;

    float init_output_value = 1.0;
    Neuron neuron1(init_output_value, null_not_needed);
    float init_threshold = 0.5;
    Neuron neuron2(null_not_needed, init_threshold);

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.8;
    neuron2.add_synapse(new_synapse);

    neuron2.set_output_value();

    float expected_result = 1.0;
    REQUIRE(neuron2.get_output_value() == expected_result);
}

TEST_CASE( "neuron - activate, via one synapse #2 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    float null_not_needed = 0.0;

    float init_output_value = 0.8;
    Neuron neuron1(init_output_value, null_not_needed);
    float init_threshold = 0.5;
    Neuron neuron2(null_not_needed, init_threshold);

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.5;
    neuron2.add_synapse(new_synapse);

    neuron2.set_output_value();

    float expected_result = 0.0;
    REQUIRE(neuron2.get_output_value() == expected_result);
}


TEST_CASE( "neuron - activate, via several synapses ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    float null_not_needed = 0.0;

    float init_output_value_1 = 0.4;
    Neuron neuron1(init_output_value_1, null_not_needed);

    float init_output_value_2 = 1.0;
    Neuron neuron2(init_output_value_2, null_not_needed);

    float init_output_value_3 = 0.3;
    Neuron neuron3(init_output_value_3, null_not_needed);

    float init_threshold = 0.666;
    Neuron neuron4(null_not_needed, init_threshold);

    Synapse new_synapse_1(neuron1, neuron4);
    new_synapse_1.weight = 0.75;
    neuron4.add_synapse(new_synapse_1);

    Synapse new_synapse_2(neuron2, neuron4);
    new_synapse_2.weight = 0.2;
    neuron4.add_synapse(new_synapse_2);

    Synapse new_synapse_3(neuron3, neuron4);
    new_synapse_3.weight = 0.5;
    neuron4.add_synapse(new_synapse_3);

    neuron4.set_output_value();

    /* Result should be = 0.4*0.75 + 1.0*0.2 + 0.3*0.5 = 0.65 < 0.666 = 0.0 */
    float expected_result = 0.0;
    REQUIRE(neuron4.get_output_value() == expected_result);
}

