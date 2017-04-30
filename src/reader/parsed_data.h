#include <vector>
#include <fstream>

/* To be used in ./bin/train */

struct TrainingData
{
    float learn_rate;
    float target_total_error;
    std::vector<int> structure;
    std::vector<std::vector<double> > data;
    std::vector<std::vector<double> > targets;
};

