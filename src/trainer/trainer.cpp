#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "trainer.h"
#include "../network/network.h"
#include "../neuron/neuron.h"

Trainer::Trainer(Network& network_init, double learning_rate_init)
    : network(network_init), backpropagation(learning_rate_init) 
{
    epoch = 0;
}

/* Each output neuron has an error score = 1/2(target-output)^2 */
double Trainer::calculate_error(Neuron& neuron)
{
    double target_value = neuron.target_value;
    double outgoing_value = neuron.outgoing_value;
    double target_out_diff = target_value - outgoing_value;
    double error = 0.5 * pow(target_out_diff, 2);
    return error;
}

/* The entire network has a fitness score, the total error */
double Trainer::calculate_total_error(std::vector<Neuron>& output_layer)
{
    double total_error_value = 0;
    for(auto& neuron: output_layer)
    {
        double error_value = calculate_error(neuron);
        total_error_value += error_value;
    }
    return total_error_value;
}

void Trainer::set_target_values(std::vector<double> new_target_values)
{
    int output_layer_size = network.output_layer.size();
    int new_target_size = new_target_values.size();

    if(output_layer_size == new_target_size)
    {
        for(int i=0; i< output_layer_size; i++)
        {
            Neuron& neuron = network.output_layer.at(i);
            neuron.target_value = new_target_values.at(i);
        }
    } else
    {
        throw std::invalid_argument( "Network requires output layer and new target_values to be the same length" );
    }
}

void Trainer::train()
{
    backpropagation.output_layer(network.output_layer);
    backpropagation.hidden_layer(network.hidden_layer);
}

