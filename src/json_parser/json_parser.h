#include "../../lib/json.hpp"

#include "../network/network.h"
#include "parsed_data.h"

namespace JsonParser
{
    nlohmann::json parse_network_data_to_json(Network& network);
    TrainingData parse_training_data_from_json(nlohmann::json json_data);
    NetworkData parse_network_data_from_json(nlohmann::json json_data);
};
