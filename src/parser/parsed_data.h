#ifndef TrainingData_h
#define TrainingData_h

#include <vector>
#include <fstream>

/* To be used in ./bin/train */

struct TrainingData
{
    double learning_rate;
    double target_total_error;
    std::vector<int> structure;
    std::vector<std::vector<double> > data;
    std::vector<std::vector<double> > targets;
};

#endif
