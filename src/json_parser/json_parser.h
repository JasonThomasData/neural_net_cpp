#ifndef JsonParser_h
#define JsonParser_h

#include "../../lib/json.hpp"

struct TrainingData;

class JsonParser
{
    private:
        JsonParser();
        static void structure_from_json(TrainingData& training_data, nlohmann::json json_data);
        static void learning_rate_from_json(TrainingData& training_data, nlohmann::json json_data);
        static void target_total_error_from_json(TrainingData& training_data, nlohmann::json json_data);
        static void training_set_from_json(TrainingData& training_data, nlohmann::json json_data);
    public:
        static TrainingData parse_training_data_from_json(nlohmann::json json_data);
};

#endif

