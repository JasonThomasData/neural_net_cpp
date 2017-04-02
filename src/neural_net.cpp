#include "assets/neuron.h"
#include "assets/synapse.h"
#include "assets/soma.h"
#include <vector>
#include <stdio.h>

/* To create a neural_network class, you'll need a few functions:
 *
 * - test if the accuracy is high enough across dataset
 * - count the number of iterations the network was trained to become reliable
 * - function to add synapses between layers of neurons (exists)
 * - function to get values for all neurons in a layer, one layer at a time (exists)
 * - a vector to contain the layers we add in place, and a function to add layers to that
 * multidimensional vector. You could call it "network". Or, you could add those layers dynamically,
 * perhaps. Maybe you could have an abstract network class and then have the number of layers
 * defined in one or more concrete classes. That concrete class would have the interface, and the
 * network would have its public variables defined and then inherited without its interface (private
 * inheritance). Then, it would be trivial to pass in the arguments at the command line.
 * 
 * So, what i want is to be able to define the type of network at the command line.
 * - `./bin/make_network -arrange 231 -i training_data.csv -o bin/networks/231`i
 * 
 * - `./bin/networks/231 -i test_data.csv`
 *
 *
 */

void connect_two_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer)
{
    int from_size = from_layer.size();
    int to_size = to_layer.size();

    for(int i=0; i<from_size; i++)
    {
        Neuron& from_neuron = from_layer.at(i);
        for(int j=0; j<to_size; j++)
        {
            Neuron& to_neuron = to_layer.at(j);
            Synapse new_synapse(from_neuron, to_neuron);
            to_neuron.add_synapse(new_synapse);
        }
    }
}

void set_output_values(std::vector<Neuron>& layer)
{
    int layer_size = layer.size();

    for(int i=0; i<layer_size; i++)
    {
        Neuron& neuron = layer.at(i);
        neuron.set_output_value();
    }
}

int main(int argc, char** argv)
{
    float init_output_value_input = 0.3;
    float init_threshold_value_input = 0.0;
    Neuron input_1(init_output_value_input, init_threshold_value_input);
    Neuron input_2(init_output_value_input, init_threshold_value_input);

    float init_output_value = 0.0;
    float init_threshold_value = 0.5;
    Neuron hidden_1(init_output_value, init_threshold_value);
    Neuron hidden_2(init_output_value, init_threshold_value);
    Neuron output_1(init_output_value, init_threshold_value);

    std::vector<Neuron> input_layer;
    std::vector<Neuron> hidden_layer;
    std::vector<Neuron> output_layer;

    input_layer.emplace_back(input_1);
    input_layer.emplace_back(input_2);
    hidden_layer.emplace_back(hidden_1);
    hidden_layer.emplace_back(hidden_2);
    output_layer.emplace_back(output_1);

    connect_two_layers(input_layer, hidden_layer);
    connect_two_layers(hidden_layer, output_layer);

    set_output_values(hidden_layer);
    set_output_values(output_layer);

};
