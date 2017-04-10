#include "trainer.h"
#include "../network/network.h"
#include "../network/neuron/neuron.h"
#include <cmath>

Trainer::Trainer(float learning_rate)
    :learning_rate(learning_rate){}

/* Each neuron has an error score = 1/2(target-output)^2 */
float Trainer::calculate_error(Neuron& neuron)
{
    float target_value = neuron.target_value;
    float output_value = neuron.get_output_value();
    float target_output_diff = target_value - output_value;
    float error = 0.5 * pow(target_output_diff, 2);
    return error;
}

/* The entire network has a fitness score, the total error */
float Trainer::calculate_total_error(std::vector<Neuron>& output_layer)
{
    float total_error_value = 0;
    for(auto& neuron: output_layer)
    {
        float error_value = calculate_error(neuron);
        total_error_value += error_value;
    }
    return total_error_value;
}

void Trainer::train()
{
    backpropagation.output_layer();
    backpropagation.hidden_layer();
}
