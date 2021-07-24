#ifndef TrainingData_h
#define TrainingData_h

#include <vector>
#include <fstream>

struct DataCollection {
    std::vector<int> structure;
};

struct TrainingDocument
{
    std::vector<double> input_values;
    std::vector<double> target_values;
};

struct TrainingData : public DataCollection
{
    double learning_rate;
    double target_total_error;
    std::vector<TrainingDocument> training_set;
};

struct SynapseData
{
    int neuron_index;
    int incoming_synapse_index;
    double incoming_synapse_weight;
};

struct NetworkData : public DataCollection
{
    std::vector<SynapseData> hidden_layer;
    std::vector<SynapseData> output_layer;
};

struct NewDocument
{
    std::vector<double> input_values;
};

struct NewData : public DataCollection
{
    std::vector<NewDocument> new_documents;
};

#endif
