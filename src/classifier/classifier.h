#ifndef Classifier_h
#define Classifier_h

#include <vector>
#include "feed_forward.h"

/* The classifier can be thought of as an agent, that manipulates the Neural Network. During
 * classification, input values are set and Neuron is told to update its values, starting with the
 * input_layer and finishing with the output layer. */

class Network;
class Neuron;

class Classifier
{
private:
    Network& network;
    void update_layer(std::vector<Neuron>& layer);
    FeedForward feed_forward;
public:
    Classifier(Network& network);
    void set_input_neurons(std::vector<int> new_input_values);
    void classify();
};

#endif
