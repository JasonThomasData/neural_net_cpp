#include "../catch.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"

TEST_CASE( "synapse - get from_neuron's weighted output_value #1 ") {

    /* InputNeuron has a public data member called output_value. This is the first layer. */
    Neuron from_neuron;
    from_neuron.outgoing_value = 0.5;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    new_synapse.weight = 1.5;

    float expected_result = 0.75;
    float actual_result = new_synapse.get_from_neuron_weighted_outgoing_value();
    REQUIRE(Approx(actual_result) == expected_result);
}

