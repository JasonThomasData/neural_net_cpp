#include "../catch.h"
#include "../../src/trainer/backpropagation.h"
#include "../../src/classifier/classifier.h"
#include "../../src/network/neuron/neuron.h"
#include "../../src/network/network.h"
#include <vector>


TEST_CASE( "backpropagation - update one neuron's error")
{

    Neuron output_neuron;
    output_neuron.target_value = 1.0;

    /* Because the neurons use the logistic function, the input is 0.3*0.1=0.03, and the logistic
     * function is = 1÷(1+2.71828^−0.03) = 0.507499
     */
    output_neuron.outgoing_value = 0.507499;

    Backpropagation backpropagation;

    /* Neuron error = (output-target)*output*(1-output)
     * (0.507499-1.0)*0.507499*(1-0.507499) = −0.123097554
     */
    backpropagation.output_layer_set_neuron_error(output_neuron);

    float actual_result = output_neuron.error_value;
    float expected_result = 0.123097554;
    expected_result = -expected_result;

    REQUIRE(Approx(actual_result) == expected_result);

}

TEST_CASE( "backpropagation - update one incoming synapse")
{

    Neuron hidden_neuron;
    hidden_neuron.outgoing_value = 0.3;

    Neuron output_neuron;
    float neuron_error = 0.009;
    Synapse synapse(hidden_neuron, output_neuron);
    synapse.weight = 0.1;

    /* For this test, the output neuron would have an output_value of 0.1 and a target of 0.0. So
     * therefore, it has a neuron_error of 0.009. The test won't actually use the output_neuron, but
     * the synapse needs it for initialisation */

    Backpropagation backpropagation;
    backpropagation.output_layer_set_synapse_weight(synapse, neuron_error);

    float actual_result = synapse.weight;
    float expected_result = 0.1 - 0.0027;

    REQUIRE(Approx(actual_result) == expected_result);

}

TEST_CASE( "backpropagation - update two incoming synapse")
{

    Neuron hidden_neuron_1;
    hidden_neuron_1.outgoing_value = 0.3;
    Neuron hidden_neuron_2;
    hidden_neuron_2.outgoing_value = 0.6;

    Neuron output_neuron;
    output_neuron.target_value = 1.0;

    Synapse synapse_1(hidden_neuron_1, output_neuron);
    synapse_1.weight = 0.4;
    Synapse synapse_2(hidden_neuron_2, output_neuron);
    synapse_2.weight = 0.12;

    /* The synapses are added to the Neuron's vector and returned as a reference */
    output_neuron.add_incoming_synapse(synapse_1);
    output_neuron.add_incoming_synapse(synapse_2);

    /* The incoming values are 0.3*0.4 + 0.6*0.12 = 0.192 
     * The sigmoid function will output 0.54785, since logistc regression = 1/(1+2.71828^-0.192) */ 
    output_neuron.outgoing_value = 0.54785;

    /* Inside the function we're testing, the Neuron's target of 1.0 will give a neuron error of
     * (outgoing_value - target_value) * outgoing_value*(1-outgoing_value) = -0.1120001491 
     * Therefore the weight change for synapse 1 will = hidden_neuron_1.outgoing_value * -0.11200
     */

    Backpropagation backpropagation;
    backpropagation.output_layer_neuron(output_neuron);

    Synapse& synapse_1_in_place = output_neuron.incoming_synapses.at(0);
    Synapse& synapse_2_in_place = output_neuron.incoming_synapses.at(1);

    float actual_result_1 = synapse_1_in_place.weight;
    float expected_result_1 = 0.4336;
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float actual_result_2 = synapse_2_in_place.weight;
    float expected_result_2 = 0.18720;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

}


TEST_CASE( "backpropagation - same as before but do forward feed first.")
{

    /* Neural network and classifier borrowed from integration/classifier.cpp */

    /* Initialise network */
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
    /* Now, the output_value should have a value of -- 0.63914
     * Also, the first neuron in the hidden_layer has an output value of 0.549834, and the second
     * has an output of 0.622459, assuming the activation functions use logistic regression.
     */

    Neuron& output_neuron = neural_network.output_layer.at(0);
    output_neuron.target_value = 1.0;

    Backpropagation backpropagation;
    backpropagation.output_layer(neural_network.output_layer);

    /*  Neuron's target of 1.0 will give a neuron error of =
     * (outgoing_value-target_value)*outgoing_value*(1-outgoing_value)
     * (0.63914-1.0)*0.63914*(1-0.63914) = −0.083228772
     * Therefore the weight change for first synapse is
     * 0.549834 * −0.083228772
     * And the second is
     * 0.622459 * −0.083228772
     */

    Synapse& synapse_1_in_place = output_neuron.incoming_synapses.at(0);
    Synapse& synapse_2_in_place = output_neuron.incoming_synapses.at(1);

    float actual_result_1 = synapse_1_in_place.weight;
    float expected_result_1 = 0.74576;
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float actual_result_2 = synapse_2_in_place.weight;
    float expected_result_2 = 0.35181;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

}

TEST_CASE( "backpropagation - test hidden_layer total_errors") 
{

    Neuron from_neuron;
    Neuron to_neuron_1;
    to_neuron_1.error_value = 0.68;
    Neuron to_neuron_2;
    to_neuron_2.error_value = 0.52;

    Synapse synapse_1(from_neuron, to_neuron_1);
    synapse_1.weight = 0.31;
    Synapse synapse_2(from_neuron, to_neuron_2);
    synapse_2.weight = 0.67;

    Synapse& synapse_1_ref = to_neuron_1.add_incoming_synapse(synapse_1);
    from_neuron.add_outgoing_synapse(synapse_1_ref);
    Synapse& synapse_2_ref = to_neuron_2.add_incoming_synapse(synapse_2);
    from_neuron.add_outgoing_synapse(synapse_2_ref);
    
    Backpropagation backpropagation;
    
    /* Result will be 0.68*0.31 + 0.52*0.67 = 0.5592*/
    float actual_result = backpropagation.hidden_layer_get_total_neuron_errors(from_neuron.outgoing_synapses);
    float expected_result = 0.5592;
    REQUIRE(Approx(actual_result) == expected_result);

}


TEST_CASE( "backpropagation - test hidden_layer set synapse")
{

    Neuron from_neuron;
    from_neuron.outgoing_value = 0.53;
    Neuron to_neuron;
    float total_neuron_errors = 0.732;

    Synapse synapse(from_neuron, to_neuron);
    synapse.weight = 0.498;

    Backpropagation backpropagation;
    backpropagation.hidden_layer_set_synapse_weight(synapse, total_neuron_errors);

    float actual_result = synapse.weight;
    float expected_result = 0.40719;
    REQUIRE(Approx(actual_result) == expected_result);

}
