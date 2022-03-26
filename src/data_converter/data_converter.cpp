#include <fstream>
#include <vector>
#include <string>

#include "../../lib/json.hpp"

#include "../simple_parser/simple_parser.h"
#include "data_converter.h"

std::ifstream DataConverter::read_file(std::string file_name)
{
    std::ifstream in_file;
    in_file.open(file_name);

    if (!in_file)
    {
        throw std::invalid_argument( "Reader could not open a file at given location." );
    }
    return in_file;
}

nlohmann::json DataConverter::convert_training_data_to_json(std::ifstream& original_data)
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
        } else if (col_1 == "#")
        {
            continue;
        } else if (col_1 == "inputs_max_values" || col_1 == "outputs_max_values")
        {
            continue;
        } else
        {
            std::cout<< col_1<< std::endl;
            std::vector<std::string> data_string_list = SimpleParser::string_vector(col_1);
            std::vector<double> parsed_input_values = SimpleParser::string_vector_double_vector(data_string_list);

            std::vector<std::string> target_string_list = SimpleParser::string_vector(col_2);
            std::vector<double> parsed_target_values = SimpleParser::string_vector_double_vector(target_string_list);

            nlohmann::json training_document = nlohmann::json::object({ {"input_values", parsed_input_values },
                                                                        {"target_values", parsed_target_values } });
            json_data["training_set"].emplace_back(training_document);
        }
    }

    return json_data;
}

nlohmann::json DataConverter::convert_new_data_to_json(std::ifstream& original_data)
{
    nlohmann::json json_data;

    json_data["new_data"] = {};

    std::string col_1;
    while (original_data >>col_1)
    {
        std::vector<std::string> data_string_list = SimpleParser::string_vector(col_1);
        std::vector<double> parsed_input_values = SimpleParser::string_vector_double_vector(data_string_list);

        json_data["new_data"].emplace_back(parsed_input_values);
    }

    return json_data;
}

//THis contains many opportunities to fail, and there are no tests... this could be better
std::stringstream DataConverter::convert_decimal_to_one_hot(std::ifstream& original_data)
{
    std::stringstream one_hot_data;
    int input_neuron_count;
    int output_neuron_count;
    std::vector<int> inputs_max_values;
    std::vector<int> outputs_max_values;
    std::string col_1, col_2;
    while (original_data >>col_1 >>col_2)
    {
        if (col_1 == "structure")
        {
            std::vector<std::string> structure_string_list = SimpleParser::string_vector(col_2);
            std::vector<int> parsed_structure = SimpleParser::string_vector_int_vector(structure_string_list);
            input_neuron_count = parsed_structure.at(0);
            output_neuron_count = parsed_structure.at(parsed_structure.size()-1);
            one_hot_data<< col_1<< " "<< col_2<< "\n";
        }
        else if (col_1 == "learning_rate" || col_1 == "target_total_error")
        {
            one_hot_data<< col_1<< " "<< col_2<< "\n";
        }
        else if (col_1 == "inputs_max_values")
        {
            //Because each training document can consist of many variables, we need to know the maximum value of each variable, for converting to one_hot
            std::vector<std::string> input_max_values_string_list = SimpleParser::string_vector(col_2);
            inputs_max_values = SimpleParser::string_vector_int_vector(input_max_values_string_list);
            one_hot_data<< col_1<< " "<< col_2<< "\n";
        }
        else if (col_1 == "outputs_max_values")
        {
            //Because each training document can consist of many variables, we need to know the maximum value of each variable, for converting to one_hot
            std::vector<std::string> outputs_max_values_string_list = SimpleParser::string_vector(col_2);
            outputs_max_values = SimpleParser::string_vector_int_vector(outputs_max_values_string_list);
            one_hot_data<< col_1<< " "<< col_2<< "\n";
        }
        else if (col_1 == "#")
        {
            continue;
        }
        else
        {
            std::vector<std::string> data_string_list = SimpleParser::string_vector(col_1);
            std::vector<int> data_int_list = SimpleParser::string_vector_int_vector(data_string_list);
            if (data_int_list.size() != inputs_max_values.size())
            {
                //This would be better to raise errors to the exe level and print everything there
                std::cout<< "The size of data "<< col_1 << " doesn't match the size of inputs_max_values ("<< inputs_max_values.size()<< ")"<< std::endl;
                exit(1);
            }
            std::vector<int> data_one_hot_vector = SimpleParser::int_vector_one_hot_vector_set_size(data_int_list, inputs_max_values);

            std::vector<std::string> labels_string_list = SimpleParser::string_vector(col_2);
            std::vector<int> labels_int_list = SimpleParser::string_vector_int_vector(labels_string_list);
            if (labels_int_list.size() != outputs_max_values.size())
            {
                //This would be better to raise errors to the exe level and print everything there
                std::cout<< "The size of label "<< col_2 << " doesn't match the size of outputs_max_values ("<< outputs_max_values.size()<< ")"<< std::endl;
                exit(1);
            }
            std::vector<int> labels_one_hot_vector = SimpleParser::int_vector_one_hot_vector_set_size(labels_int_list, outputs_max_values);

            std::string data_string = SimpleParser::int_vector_to_string(data_one_hot_vector);
            std::string labels_string = SimpleParser::int_vector_to_string(labels_one_hot_vector);

            one_hot_data<< data_string<< " "<< labels_string<< "\n";

        }
    }

    return one_hot_data;
}

