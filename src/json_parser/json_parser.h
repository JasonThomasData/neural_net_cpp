#ifndef JsonParser_h
#define JsonParser_h

#include "../../lib/json.hpp"
#include "../network/network.h"
#include "from_json.h"
#include "to_json.h"

class TrainingData;

class JsonParser
{
    private:
        FromJson from_json;
        ToJson to_json;
    public:
        JsonParser();
        nlohmann::json parse_network_data_to_json(Network& network);
        TrainingData parse_training_data_from_json(nlohmann::json json_data);
};

#endif
