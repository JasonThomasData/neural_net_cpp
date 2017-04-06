#include "../catch.h"
#include "../../src/network/neuron/input.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"

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
    REQUIRE(Approx(actual_result) == expected_result);
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
    REQUIRE(Approx(actual_result) == expected_result);
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
    REQUIRE(Approx(actual_result) == expected_result);
}
