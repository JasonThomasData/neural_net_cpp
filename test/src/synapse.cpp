#include "../../lib/catch.h"
#include "../../src/synapse/synapse.h"
#include "../../src/neuron/neuron.h"

TEST_CASE( "synapse - integration test - get from_neuron's weighted output_value #1 ") {

    /* InputNeuron has a public data member called output_value. This is the first layer. */
    Neuron from_neuron;
    from_neuron.outgoing_value = 0.5;

    Neuron to_neuron;

    Synapse new_synapse(from_neuron, to_neuron);
    double weight = 1.5;
    new_synapse.set_weight(weight);

    float expected_result = 0.75;
    float actual_result = new_synapse.get_from_neuron_weighted_outgoing_value();
    REQUIRE(Approx(actual_result) == expected_result);
}

