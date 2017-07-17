#ifndef ISynapse_h
#define ISynapse_h

class Neuron;

class ISynapse
{
    virtual double get_weight() =0;
    virtual void set_weight(double new_weight) =0;
    virtual Neuron& get_from_neuron() =0;
    virtual Neuron& get_to_neuron() =0;
    virtual double get_from_neuron_weighted_outgoing_value() =0;
};

#endif
