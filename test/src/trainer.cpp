#include <vector>
#include "../../lib/catch.h"
#include "../../src/trainer/trainer.h"
#include "../../src/network/neuron/neuron.h"
#include "../../src/network/network.h"

TEST_CASE( "trainer - integration test - get total_error for network")
{

    Neuron output_neuron_1;
    output_neuron_1.target_value = 0.0;
    output_neuron_1.outgoing_value = 0.18;
    Neuron output_neuron_2;
    output_neuron_2.target_value = 1.0;
    output_neuron_2.outgoing_value = 0.89;

    double learning_rate = 0.0; /* used in backpropagation */

    // Neurons contain references to unique_ptrs inside, so we need std::move() to avoid calling
    // copy constructor.
    std::vector<Neuron> output_layer;
    output_layer.emplace_back(std::move(output_neuron_1));
    output_layer.emplace_back(std::move(output_neuron_2));

    Network network({2, 2, 2}); /* Not actually used, but the trainer needs it for init */
    Trainer trainer(network, learning_rate);

    float actual_result = trainer.calculate_total_error(output_layer);
    float expected_result = 0.02225;

    REQUIRE(Approx(actual_result) == expected_result);

}

TEST_CASE( "trainer - integration test - set target_values")
{

    std::vector<int> layer_counts;

    int input_count = 2;
    int hidden_count = 3;
    int output_count = 2;

    layer_counts.emplace_back(input_count);
    layer_counts.emplace_back(hidden_count);
    layer_counts.emplace_back(output_count);

    Network neural_network(layer_counts);

    double learning_rate = 0.0; /* used in backpropagation */
    Trainer trainer(neural_network, learning_rate);

    std::vector<double> update_values;
    update_values.emplace_back(0.3);
    update_values.emplace_back(0.7);

    trainer.set_target_values(update_values);

    float actual_result_1 = neural_network.output_layer.at(0).target_value;
    float expected_result_1 = 0.3;
    REQUIRE(Approx(actual_result_1) == expected_result_1);

    float actual_result_2 = neural_network.output_layer.at(1).target_value;
    float expected_result_2 = 0.7;
    REQUIRE(Approx(actual_result_2) == expected_result_2);

}

TEST_CASE( "trainer - integration test - set target_values, will fail because length of vectors don't match")
{

    std::vector<int> layer_counts;

    int input_count = 2;
    int hidden_count = 3;
    int output_count = 1;

    layer_counts.emplace_back(input_count);
    layer_counts.emplace_back(hidden_count);
    layer_counts.emplace_back(output_count);

    Network neural_network(layer_counts);

    double learning_rate = 0.0; /* used in backpropagation */
    Trainer trainer(neural_network, learning_rate);

    std::vector<double> update_values;
    update_values.emplace_back(0.0);
    update_values.emplace_back(1.0);
    update_values.emplace_back(0.0);

    REQUIRE_THROWS( trainer.set_target_values(update_values) );

}
