#ifndef FromJson_h
#define FromJson_h

#include "../../lib/json.hpp"
#include "../network/network.h"

struct TrainingData;

class FromJson
{
    public:
        FromJson();
        void structure(TrainingData& training_data, nlohmann::json json_data);
        void learning_rate(TrainingData& training_data, nlohmann::json json_data);
        void target_total_error(TrainingData& training_data, nlohmann::json json_data);
        void training_set(TrainingData& training_data, nlohmann::json json_data);
};

#endif

