#include "../../lib/json.hpp"

#include "../network/network.h"
#include "parsed_data.h"

namespace FromJson
{
    void structure(TrainingData& training_data, nlohmann::json json_data);
    void learning_rate(TrainingData& training_data, nlohmann::json json_data);
    void target_total_error(TrainingData& training_data, nlohmann::json json_data);
    void training_set(TrainingData& training_data, nlohmann::json json_data);
};

