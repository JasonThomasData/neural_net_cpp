#include "../catch.h"
#include "../../src/network/input_neuron/input_neuron.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"
#include "../../src/network/soma/soma.h"

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

    /* Usually, this is a data member of Neuron class */
    std::vector <Synapse> incoming_synapses;
    incoming_synapses.emplace_back(new_synapse_1);
    incoming_synapses.emplace_back(new_synapse_2);

    Soma soma;

    /* Result = 0.7*0.5 + 0.25*0.8 = 0.55 */
    float expected_result = 0.55;
    float actual_result = soma.calculate_incoming_values(incoming_synapses);
    REQUIRE(Approx(actual_result) == expected_result);
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
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float test_value_2 = 0.5;
    float actual_result_2 = soma.activate(test_value_2);
    float expected_result_2 = 0.622459;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

    float test_value_3 = 1.0;
    float actual_result_3 = soma.activate(test_value_3);
    float expected_result_3 = 0.73106;
    REQUIRE(Approx(actual_result_3) == expected_result_3);

    /* I can't think of a situation where incoming values would be below zero, unless the weights on
     * synapses were negative, and I guess that could happen. It could occur if the activation was
     * using another function, like TanH.
     */
    float test_value_4 = -1.0;
    float actual_result_4 = soma.activate(test_value_4);
    float expected_result_4 = 0.26894;
    REQUIRE(Approx(actual_result_4) == expected_result_4);
}
