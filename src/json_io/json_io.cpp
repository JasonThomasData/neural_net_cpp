#include <fstream>
#include <iostream>
#include <vector>
#include <stdexcept>

#include "../../lib/json.hpp"

#include "json_io.h"
#include "../json_parser/parsed_data.h"
#include "../json_parser/json_parser.h"
#include "../network/network.h"

TrainingData JsonIO::read_training_data(std::string file_name)
{
    nlohmann::json json_data = read_file(file_name);
    TrainingData training_data = JsonParser::parse_training_data_from_json(json_data);
    return training_data;
}

void JsonIO::save_network_data(std::string file_name, Network& network)
{
    nlohmann::json json_data = JsonParser::parse_network_data_to_json(network);
    save_json_data(file_name, json_data);
}

NetworkData JsonIO::read_network_data(std::string file_name)
{
    nlohmann::json json_data = read_file(file_name);
    NetworkData network_data = JsonParser::parse_network_data_from_json(json_data);
    return network_data;
}

NewData JsonIO::read_new_data(std::string file_name)
{
    nlohmann::json json_data = read_file(file_name);
    NewData new_data = JsonParser::parse_new_data_from_json(json_data);
    return new_data;
}

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

void JsonIO::save_json_data(std::string out_path, nlohmann::json out_data)
{
    std::ofstream filestream;
    filestream.open(out_path);
    filestream << out_data << std::endl;
    filestream.close();
}
