#include "../../lib/json.hpp"

#include "../json_parser/parsed_data.h"
#include "../network/network.h"

namespace JsonIO
{
    nlohmann::json read_file(std::string file_name);
    TrainingData read_training_data(std::string file_name);
    NetworkData read_network_data(std::string file_name);
    NewData read_new_data(std::string file_name);
    void save_network_data(std::string file_name, Network& network);
    void save_json_data(std::string file_name, nlohmann::json json_data);
};
