#include <fstream>
#include <vector>
#include "../../lib/json.hpp"

namespace DataConverter
{
    std::ifstream read_file(std::string file_name);
    nlohmann::json convert_to_json(std::ifstream& original_data);
};
