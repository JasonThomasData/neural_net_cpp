#ifndef Classifier_h
#define Classifier_h

#include <vector>
#include "../network/network.h"
#include "../network/neuron/neuron.h"

/* The classifier can be thought of as an agent, that manipulates the Neural Network. During
 * classification, input values are set and Neuron is told to update its values, starting with the
 * input_layer and finishing with the output layer. */

class Classifier
{
private:
    Network& network;
    void update_layer(std::vector<Neuron>& layer);
public:
    Classifier(Network& network);
    void feed_forward();
    void set_input_neurons(std::vector<int> new_input_values);
};

#endif
