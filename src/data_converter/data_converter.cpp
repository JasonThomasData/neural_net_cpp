#include <fstream>
#include <vector>
#include <string>

#include "../../lib/json.hpp"

#include "../simple_parser/simple_parser.h"
#include "data_converter.h"

std::ifstream DataConverter::read_file(std::string& file_name)
{
    std::ifstream in_file;
    in_file.open(file_name);

    if (!in_file)
    {
        throw std::invalid_argument( "Reader could not open a file at given location." );
    }
    return in_file;
}

nlohmann::json DataConverter::convert_to_json(std::ifstream& original_data)
{

    nlohmann::json json_data;

    json_data["training_set"] = {};

    std::string col_1, col_2;
    while (original_data >>col_1 >>col_2)
    {
        if (col_1 == "structure")
        {
            std::vector<std::string> structure_string_list = SimpleParser::string_vector(col_2);
            std::vector<int> parsed_structure = SimpleParser::string_vector_int_vector(structure_string_list);
            json_data["structure"] = parsed_structure;
        } else if (col_1 == "learning_rate")
        {
            json_data["learning_rate"] = SimpleParser::to_double(col_2);
        } else if (col_1 == "target_total_error")
        {
            json_data["target_total_error"] = SimpleParser::to_double(col_2);
        } else
        {
            std::vector<std::string> data_string_list = SimpleParser::string_vector(col_1);
            std::vector<double> parsed_input_values = SimpleParser::string_vector_double_vector(data_string_list);

            std::vector<std::string> target_string_list = SimpleParser::string_vector(col_2);
            std::vector<double> parsed_target_values = SimpleParser::string_vector_double_vector(target_string_list);

            nlohmann::json training_value_target_pair = nlohmann::json::object({ {"input_values", parsed_input_values },
                                                                                 {"target_values", parsed_target_values } });
            json_data["training_set"].emplace_back(training_value_target_pair);
        }
    }

    return json_data;
}

void DataConverter::save_data(std::string& out_path, nlohmann::json& out_data)
{
    std::ofstream out_file(out_path);
    out_file << std::setw(0) << out_data << std::endl;
}
