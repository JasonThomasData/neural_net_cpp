#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "../../lib/json.hpp"

#include "json_io.h"
#include "../json_parser/parsed_data.h"
#include "../json_parser/json_parser.h"
#include "../network/network.h"

JsonIO::JsonIO(){}

TrainingData JsonIO::read_training_data(std::string file_name)
{
    nlohmann::json json_data = read_file(file_name);
    TrainingData training_data = JsonParser::parse_training_data_from_json(json_data);
    return training_data;
}

void JsonIO::save_network_data(std::string file_name, Network network) {}

nlohmann::json JsonIO::read_file(std::string file_name)
{
    try
    {
        std::ifstream file_data(file_name);
        nlohmann::json json_data;
        file_data >> json_data;
        return json_data;
    }
    catch (const nlohmann::detail::parse_error& exception)
    {
        std::cout<< "check file exists + file format"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void JsonIO::save_file(std::string file_name, nlohmann::json json_data) {}
