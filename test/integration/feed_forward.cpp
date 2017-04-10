#include "../catch.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"
#include "../../src/classifier/feed_forward.h"

TEST_CASE( "feed_forward - test the sum function works - combine all incoming values")
{
    /* Both synapses have the same to neuron and it's not used in the function.
     */

    Neuron to_neuron;

    Neuron from_neuron_1;
    from_neuron_1.outgoing_value = 0.7;
    Neuron from_neuron_2;
    from_neuron_2.outgoing_value = 0.25;

    Synapse new_synapse_1(from_neuron_1, to_neuron);
    new_synapse_1.weight = 0.5;
    Synapse new_synapse_2(from_neuron_2, to_neuron);
    new_synapse_2.weight = 0.8;

    /* Usually, this is a data member of Neuron class */
    std::vector <Synapse> incoming_synapses;
    incoming_synapses.emplace_back(new_synapse_1);
    incoming_synapses.emplace_back(new_synapse_2);

    FeedForward feed_forward;

    /* Result = 0.7*0.5 + 0.25*0.8 = 0.55 */
    float expected_result = 0.55;
    float actual_result = feed_forward.calculate_incoming_values(incoming_synapses);
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "feed_forward - test the logistic/ activation function works.")
{
    /* This is logistic regression, check the feed_forward.cpp file */
    /* Also, watch tests that return floats, as returned floats have a max precision of 5 decimal
     * places.
     */

    FeedForward feed_forward;

    float test_value_1 = 0.0;
    float actual_result_1 = feed_forward.activate(test_value_1);
    float expected_result_1 = 0.5;
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float test_value_2 = 0.5;
    float actual_result_2 = feed_forward.activate(test_value_2);
    float expected_result_2 = 0.622459;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

    float test_value_3 = 1.0;
    float actual_result_3 = feed_forward.activate(test_value_3);
    float expected_result_3 = 0.73106;
    REQUIRE(Approx(actual_result_3) == expected_result_3);

    /* I can't think of a situation where incoming values would be below zero, unless the weights on
     * synapses were negative, and I guess that could happen. It could occur if the activation was
     * using another function, like TanH.
     */
    float test_value_4 = -1.0;
    float actual_result_4 = feed_forward.activate(test_value_4);
    float expected_result_4 = 0.26894;
    REQUIRE(Approx(actual_result_4) == expected_result_4);
}

TEST_CASE( "feed_forward - activate one Neuron, via one incoming synapse #1 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    Neuron neuron1;
    neuron1.outgoing_value = 1.0;

    Neuron neuron2;

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.8;
    neuron2.add_incoming_synapse(new_synapse);

    /* Incoming weights are equal to 1.0*0.8 = 0.8 */
    FeedForward feed_forward;
    neuron2.incoming_values = feed_forward.calculate_incoming_values(neuron2.incoming_synapses);
    neuron2.outgoing_value =feed_forward.activate(neuron2.incoming_values);

    float expected_result = 0.689974;
    float actual_result = neuron2.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "neuron - activate, via one incoming synapse #2 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    Neuron neuron1;
    neuron1.outgoing_value = 0.8;

    Neuron neuron2;

    Synapse new_synapse(neuron1, neuron2);
    new_synapse.weight = 0.5;
    neuron2.add_incoming_synapse(new_synapse);

    /* Incoming weights are equal to 0.5*0.8 = 0.4*/
    FeedForward feed_forward;
    neuron2.incoming_values = feed_forward.calculate_incoming_values(neuron2.incoming_synapses);
    neuron2.outgoing_value =feed_forward.activate(neuron2.incoming_values);

    float expected_result = 0.598688;
    float actual_result = neuron2.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "neuron - activate, via several incoming synapses, and only calling update() ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    Neuron neuron1;
    neuron1.outgoing_value = 0.4;

    Neuron neuron2;
    neuron2.outgoing_value = 1.0;

    Neuron neuron3;
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

    FeedForward feed_forward;
    feed_forward.update_neuron(neuron4);

    /* Incoming values should be = 0.4*0.75 + 1.0*0.2 + 0.3*0.5 = 0.65 */
    float expected_result = 0.65701;
    float actual_result = neuron4.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}
