#include "../catch.h"
#include "../../src/network/input_neuron/input_neuron.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"

TEST_CASE( "synapse - get from_neuron's weighted output_value #1 ") {

    /* InputNeuron has a public data member called output_value. This is the first layer. */
    InputNeuron from_neuron;
    from_neuron.outgoing_value = 0.5;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.5;

    float expected_result = 0.75;
    float actual_result = new_synapse.get_from_neuron_weighted_outgoing_value();
    REQUIRE(Approx(actual_result) == expected_result);
}

TEST_CASE( "synapse - get from_neuron's original output_value #2 ") {

    InputNeuron from_neuron;
    from_neuron.outgoing_value = 4.0;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 0.75; /* This proves this value is ignored in fetching the original */

    float expected_result = 4.0;
    float actual_result = new_synapse.get_from_neuron_outgoing_value();
    REQUIRE(Approx(actual_result) == expected_result);
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
