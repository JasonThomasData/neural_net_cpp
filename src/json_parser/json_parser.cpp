#include "../../lib/json.hpp"

#include "parsed_data.h"
#include "json_parser.h"

TrainingData JsonParser::parse_training_data_from_json(nlohmann::json json_data)
{
    TrainingData training_data;
    structure_from_json(training_data, json_data);
    learning_rate_from_json(training_data, json_data);
    target_total_error_from_json(training_data, json_data);
    training_set_from_json(training_data, json_data);
    return training_data;
}

void JsonParser::structure_from_json(TrainingData& training_data, nlohmann::json json_data)
{
    try
    {
        for(int neurons_in_layer: json_data["structure"])
        {
            training_data.structure.emplace_back(neurons_in_layer);
        }
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check structure[int]"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void JsonParser::learning_rate_from_json(TrainingData& training_data, nlohmann::json json_data)
{
    try
    {
        training_data.learning_rate = json_data["learning_rate"];
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check learning_rate"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        throw exception;
    }
}

void JsonParser::target_total_error_from_json(TrainingData& training_data, nlohmann::json json_data)
{
    try
    {
        training_data.target_total_error = json_data["target_total_error"];
    }
    catch (const std::exception& exception)
    {
        std::cout<< "check target_total_error"<< std::endl;
        std::cout<< exception.what()<< std::endl;
        exit(1);
    }
}

void JsonParser::training_set_from_json(TrainingData& training_data, nlohmann::json json_data)
{
    for(auto training_example: json_data["training_set"])
    {
        try
        {
            std::vector<double> input_values = training_example["input_values"];
            training_data.input_values.emplace_back(input_values);
        }
        catch (const std::exception& exception)
        {
            std::cout<< "check training_set[n].input_values"<< std::endl;
            std::cout<< exception.what()<< std::endl;
            throw exception;
        }

        try
        {
            std::vector<double> target_values = training_example["target_values"];
            training_data.target_values.emplace_back(target_values);
        }
        catch (const std::exception& exception)
        {
            std::cout<< "check training_set[n].output_values"<< std::endl;
            std::cout<< exception.what()<< std::endl;
            throw exception;
        }
    }
}
