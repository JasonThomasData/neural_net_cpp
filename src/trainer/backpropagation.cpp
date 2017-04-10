#include "backpropagation.h"
#include "../network/neuron/neuron.h"
#include "../network/synapse/synapse.h"
#include <vector>

Backpropagation::Backpropagation(){}

/* The change of each incoming_synapse depends on the output_value of the neuron before the Synapse'
 * weight was applied - the original output_value. Might want to add a learning rate here in
 * future. The from_neuron_outgoing_value is the final part of the delta rule for the output_layer
 * neurons.
 */
void Backpropagation::output_layer_set_synapse_weight(Synapse& synapse, float neuron_error)
{
    float from_neuron_outgoing_value = synapse.from_neuron.outgoing_value;
    float synapse_weight_change = neuron_error * from_neuron_outgoing_value;
    synapse.weight -= synapse_weight_change;
}

/* We need to find the neuron error of the output layer neurons for the doing the delta rule. The
 * error is used to update the synapses coming into the output neurons, and those coming into the
 * hidden layer also, therefore we should save the result as a data member in the Neuron to retrieve
 * it later.
 */
void Backpropagation::output_layer_set_neuron_error(Neuron& neuron)
{
    float target_value = neuron.target_value;
    float outgoing_value = neuron.outgoing_value;
    neuron.error_value = (outgoing_value - target_value) * outgoing_value*(1 - outgoing_value);
}

/* For neurons in the output layer, use the delta rule, to get the new weight for any one synapse.
 * d = -(target_value - output_value) * output_value(1 - output_value) * from_neuron_output_value
 * the first step can be rewritten as output_value - target_value. The first parts of that function
 * to get the neuron's error are done once only for every round of backpropagation, and the error
 * is used with several Synpase weights later on. This uses the partial derivative of the logistic
 * function 
 */
void Backpropagation::output_layer_neuron(Neuron& neuron)
{
    output_layer_set_neuron_error(neuron);
    for(auto& synapse: neuron.incoming_synapses)
    {
        output_layer_set_synapse_weight(synapse, neuron.error_value);
    }
}

void Backpropagation::output_layer(std::vector<Neuron>& output_layer)
{
    for(auto& neuron: output_layer)
    {
        output_layer_neuron(neuron);
    }
}

/* This also uses the partial derivative of the logistic function, out(1-out), and would need to
 * change for a different activation function.
 */
void Backpropagation::hidden_layer_set_synapse_weight(Synapse& synapse, float total_neuron_errors)
{
    float from_neuron_outgoing_value = synapse.from_neuron.outgoing_value;
    float synapse_weight_change = synapse.weight * from_neuron_outgoing_value*(1-from_neuron_outgoing_value) * total_neuron_errors;
    synapse.weight -= synapse_weight_change;
}

float Backpropagation::hidden_layer_get_total_neuron_errors(std::vector<Synapse>& outgoing_synapses)
{
    float total_errors = 0.0;
    for(auto& synapse: outgoing_synapses)
    {
        float error_to_add = synapse.weight * synapse.to_neuron.error_value;
        total_errors += error_to_add;
    }
    return total_errors;
}

/* Changing the weights of Synapses for hidden_layer Neurons needs to take the errors from the next
 * layer's Neurons into account.
 */
void Backpropagation::hidden_layer_neuron(Neuron& neuron)
{
    float total_neuron_errors = hidden_layer_get_total_neuron_errors(neuron.outgoing_synapses);
    for(auto& synapse: neuron.incoming_synapses)
    {
        hidden_layer_set_synapse_weight(synapse, total_neuron_errors);
    }
}

void Backpropagation::hidden_layer(std::vector<Neuron>& hidden_layer)
{
    for(auto& neuron: hidden_layer)
    {
        hidden_layer_neuron(neuron);
    }
}
