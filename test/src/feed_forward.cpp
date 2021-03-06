#include "../../lib/catch.h"
#include "../../src/synapse/synapse.h"
#include "../../src/synapse/i_synapse.h"
#include "../../src/neuron/neuron.h"
#include "../../src/classifier/feed_forward.h"
#include <memory>

TEST_CASE( "feed_forward - integration test - test the sum function works - combine all incoming values")
{
    /* Both synapses have the same to neuron and it's not used in the function.
     */

    Neuron to_neuron;

    Neuron from_neuron_1;
    from_neuron_1.outgoing_value = 0.7;
    Neuron from_neuron_2;
    from_neuron_2.outgoing_value = 0.25;

    std::unique_ptr<ISynapse> new_synapse_1 = std::make_unique<Synapse>(from_neuron_1, to_neuron);
    double weight_1 = 0.5;
    new_synapse_1->set_weight(weight_1);
    std::unique_ptr<ISynapse> new_synapse_2 = std::make_unique<Synapse>(from_neuron_2, to_neuron);
    double weight_2 = 0.8;
    new_synapse_2->set_weight(weight_2);

    /* Usually, this is a data member of Neuron class */
    std::vector<std::unique_ptr<ISynapse>> incoming_synapses;
    incoming_synapses.emplace_back(std::move(new_synapse_1));
    incoming_synapses.emplace_back(std::move(new_synapse_2));

    /* Result = 0.7*0.5 + 0.25*0.8 = 0.55 */
    float expected_result = 0.55;
    float actual_result = FeedForward::calculate_incoming_values(incoming_synapses);
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "feed_forward - unit test - test the logistic/ activation function works.")
{
    /* This is logistic regression, check the feed_forward.cpp file */
    /* Also, watch tests that return floats, as returned floats have a max precision of 5 decimal
     * places.
     */

    //FeedForward feed_forward;

    float test_value_1 = 0.0;
    float actual_result_1 = FeedForward::activate(test_value_1);
    float expected_result_1 = 0.5;
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float test_value_2 = 0.5;
    float actual_result_2 = FeedForward::activate(test_value_2);
    float expected_result_2 = 0.622459;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

    float test_value_3 = 1.0;
    float actual_result_3 = FeedForward::activate(test_value_3);
    float expected_result_3 = 0.73106;
    REQUIRE(Approx(actual_result_3) == expected_result_3);

    /* I can't think of a situation where incoming values would be below zero, unless the weights on
     * synapses were negative, and I guess that could happen. It could occur if the activation was
     * using another function, like TanH.
     */
    float test_value_4 = -1.0;
    float actual_result_4 = FeedForward::activate(test_value_4);
    float expected_result_4 = 0.26894;
    REQUIRE(Approx(actual_result_4) == expected_result_4);
}

TEST_CASE( "feed_forward - integration test - activate one Neuron, via one incoming synapse #1 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    Neuron neuron1;
    neuron1.outgoing_value = 1.0;

    Neuron neuron2;

    std::unique_ptr<ISynapse> new_synapse = std::make_unique<Synapse>(neuron1, neuron2);
    double weight = 0.8;
    new_synapse->set_weight(weight);

    neuron2.add_incoming_synapse(std::move(new_synapse));

    /* Incoming weights are equal to 1.0*0.8 = 0.8 */
    neuron2.incoming_values = FeedForward::calculate_incoming_values(neuron2.incoming_synapses);
    neuron2.outgoing_value = FeedForward::activate(neuron2.incoming_values);

    float expected_result = 0.689974;
    float actual_result = neuron2.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "neuron - integration test - activate, via one incoming synapse #2 ") {
    /* For a neuron to activate, the synapses coming in must all have weights, and the neurons those
     * synapses originate from must have an output_value
     */

    Neuron neuron1;
    neuron1.outgoing_value = 0.8;

    Neuron neuron2;

    std::unique_ptr<ISynapse> new_synapse = std::make_unique<Synapse>(neuron1, neuron2);
    double weight = 0.5;
    new_synapse->set_weight(weight);

    neuron2.add_incoming_synapse(std::move(new_synapse));

    /* Incoming weights are equal to 0.5*0.8 = 0.4*/
    neuron2.incoming_values = FeedForward::calculate_incoming_values(neuron2.incoming_synapses);
    neuron2.outgoing_value = FeedForward::activate(neuron2.incoming_values);

    float expected_result = 0.598688;
    float actual_result = neuron2.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "neuron -  integration test - activate, via several incoming synapses, and only calling update() ") {
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

    std::unique_ptr<ISynapse> new_synapse_1 = std::make_unique<Synapse>(neuron1, neuron4);
    double weight_1 = 0.75;
    new_synapse_1->set_weight(weight_1);

    std::unique_ptr<ISynapse> new_synapse_2 = std::make_unique<Synapse>(neuron2, neuron4);
    double weight_2 = 0.2;
    new_synapse_2->set_weight(weight_2);

    std::unique_ptr<ISynapse> new_synapse_3 = std::make_unique<Synapse>(neuron3, neuron4);
    double weight_3 = 0.5;
    new_synapse_3->set_weight(weight_3);

    neuron4.add_incoming_synapse(std::move(new_synapse_1));
    neuron4.add_incoming_synapse(std::move(new_synapse_2));
    neuron4.add_incoming_synapse(std::move(new_synapse_3));

    FeedForward::update_neuron(neuron4);

    /* Incoming values should be = 0.4*0.75 + 1.0*0.2 + 0.3*0.5 = 0.65 */
    float expected_result = 0.65701;
    float actual_result = neuron4.outgoing_value;
    REQUIRE(Approx(actual_result) == expected_result);
}
