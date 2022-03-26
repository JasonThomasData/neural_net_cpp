#include <fstream>
#include <vector>
#include "../../lib/json.hpp"

namespace DataConverter
{
    std::ifstream read_file(std::string file_name);
    nlohmann::json convert_training_data_to_json(std::ifstream& original_data);
    nlohmann::json convert_new_data_to_json(std::ifstream& original_data);
    std::stringstream convert_decimal_to_one_hot(std::ifstream& original_data);
};
