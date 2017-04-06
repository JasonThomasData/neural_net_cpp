#include "../catch.h"
#include "../../src/network/input_neuron/input_neuron.h"
#include "../../src/network/synapse/synapse.h"
#include "../../src/network/neuron/neuron.h"

TEST_CASE( "neuron - test one synapse is added and a reference to it is returned") {
    
    class Synapse{
    public:
        float weight = 0.5;
        Synapse();
    };

    Synapse mock_synapse;

    Neuron neuron;

    Synapse& added_synapse_reference = neuron.add_incoming_synapse(mock_synapse);

    float expected_result = 0.5;
    float actual_result = added_synapse_reference.weight;
    REQUIRE(Approx(actual_result) == expected_result);

}
