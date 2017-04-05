#ifndef Soma_h
#define Soma_h

#include <vector>

/* A soma is a cell body, and according to this explainer -
 * http://study.com/academy/lesson/what-is-a-cell-body-definition-function-types.html
 * - soma a is responsible for combining all incoming values from other neurons (via Synapses), and deciding
 * whether to send an output signal along its own axon (which we have called output_value).
 */

class Synapse;

class Soma
{
    public:
        Soma();
        float calculate_incoming_values(std::vector <Synapse>&);
        float activate(float incoming_values);
};
#endif
