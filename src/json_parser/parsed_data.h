#ifndef TrainingData_h
#define TrainingData_h

#include <vector>
#include <fstream>

/* To be used in ./bin/train */

struct TrainingDocument 
{
    std::vector<double> input_values;
    std::vector<double> target_values;
};

struct TrainingData
{
    double learning_rate;
    double target_total_error;
    std::vector<int> structure;
    std::vector<TrainingDocument> training_set;
};

#endif
