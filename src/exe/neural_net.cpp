#include "../network/input_neuron/input_neuron.h"
#include "../network/neuron/neuron.h"
#include "../network/synapse/synapse.h"
#include "../network/soma/soma.h"
#include <vector>

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



/* Need this duplication until I can understand how to pass around the NeuronInterface.
 * A key difference is one needs the add_outgoing_synapse and the other doesn't.
 * Is it possible to define virtual functions for both of those functions, add_incoming_synapse and
 * add_outgoing_synapse, and override the functions when and where we need to. The reason for this,
 * is the InputNeuron does not have a list of outgoing Synapses.
 */
void connect_input_hidden_layer(std::vector<InputNeuron>& from_layer, std::vector<Neuron>& to_layer)
{
    for(auto& from_neuron: from_layer)
    {
        for(auto& to_neuron: to_layer)
        {
            Synapse new_synapse(from_neuron, to_neuron);
            to_neuron.add_incoming_synapse(new_synapse);
        }
    }
}
void connect_two_layers(std::vector<Neuron>& from_layer, std::vector<Neuron>& to_layer)
{
    for(auto& from_neuron: from_layer)
    {
        for(auto& to_neuron: to_layer)
        {
            Synapse new_synapse(from_neuron, to_neuron);
            Synapse& added_synapse = to_neuron.add_incoming_synapse(new_synapse);
            from_neuron.add_outgoing_synapse(added_synapse);
        }
    }
}

/* Put the function call inside another called feed_forward */
void update_output_values(std::vector<Neuron>& layer)
{
    int layer_size = layer.size();

    for(int i=0; i<layer_size; i++)
    {
        Neuron& neuron = layer.at(i);
        neuron.set_in_out_values();
    }
}


int main(int argc, char** argv)
{
    /* The output_value of InputNeuron can be set after initialising. */
    InputNeuron input_1;
    InputNeuron input_2;
    input_1.outgoing_value = 0.5;
    input_2.outgoing_value = 1.2;

    Neuron hidden_1;
    Neuron hidden_2;
    Neuron output_1;

    std::vector<InputNeuron> input_layer;
    std::vector<Neuron> hidden_layer;
    std::vector<Neuron> output_layer;

    input_layer.emplace_back(input_1);
    input_layer.emplace_back(input_2);
    hidden_layer.emplace_back(hidden_1);
    hidden_layer.emplace_back(hidden_2);
    output_layer.emplace_back(output_1);

    connect_input_hidden_layer(input_layer, hidden_layer);
    connect_two_layers(hidden_layer, output_layer);

    update_output_values(hidden_layer);
    update_output_values(output_layer);

};
